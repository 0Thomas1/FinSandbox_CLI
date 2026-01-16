#include "MarketData.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>     // for system()

using json = nlohmann::json;

void MarketData::loadFromAPI(const std::string& symbol, const std::string& apiKey){
    std::string outFile = "../data/" + symbol + ".json";

    std::string url =
        "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY"
        "&symbol=" + symbol +
        "&apikey=" + apiKey +
        "&outputsize=full";
    std::string command = "curl -s \"" + url + "\" -o " + outFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Curl failed for " << symbol << " code: " << code <<"\n";
        return;
    }
    std::ifstream file(outFile);
    if (!file.is_open()) {
        std::cerr << "Error opening downloaded file " << outFile << "\n";
        return;
    }

    json j;
    file >> j;

    if (!j.contains("Time Series (Daily)")) {
        std::cerr << "Unexpected JSON format for " << symbol << "\n";
        return;
    }

    auto series = j["Time Series (Daily)"];
    std::vector<PriceRecord> records;
    records.reserve(series.size());

    for (auto& [date, values] : series.items()) {
        PriceRecord rec;
        rec.date   = date;
        rec.open   = std::stod(values["1. open"].get<std::string>());
        rec.high   = std::stod(values["2. high"].get<std::string>());
        rec.low    = std::stod(values["3. low"].get<std::string>());
        rec.close  = std::stod(values["4. close"].get<std::string>());
        rec.volume = std::stol(values["5. volume"].get<std::string>());
        records.push_back(rec);
    }

    data[symbol] = records;
    std::cout << "Fetched " << records.size() << " daily records for " << symbol << " from Alpha Vantage.\n";

}

const std::vector<PriceRecord>& MarketData::getPrices(const std::string& symbol) const {
    auto it = data.find(symbol);
    if (it != data.end()) {
        return it->second;
    }
    static const std::vector<PriceRecord> empty;
    return empty;
}