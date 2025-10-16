#include "MarketData.h"
#include <iostream>

#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> loadEnv(const std::string& filename) {
    std::unordered_map<std::string, std::string> env;
    std::ifstream file;

    file.open(filename);
    if(!file.is_open()){
        std::cout <<"File not open.\n";

        return env;
    }
    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            env[key] = value;
        }
    }
    return env;
}

int main() {
    MarketData md;
    auto env = loadEnv(".env");
    std::string apiKey = env.count("API_KEY") ? env["API_KEY"] : "";
    if (apiKey.empty()) {
        std::cerr << "API_KEY not found in .env file.\n";
        return 1;
    }

    md.loadFromAPI("AAPL", apiKey);

    const auto& prices = md.getPrices("AAPL");
    if (!prices.empty()) {
        std::cout << "Latest Close: " << prices.front().close << "\n";
    } else {
        std::cout << "No price data available for AAPL.\n";
    }
    return 0;

    // auto env = loadEnv(".env");
    // std::cout << env["API_KEY"] << "\n";
    // return 0;
}
