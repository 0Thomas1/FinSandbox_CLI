#include "MarketData.h"
#include "Portfolio.h"
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

void toupper(std::string& string){
    for(char& c :string){
        c = std::toupper(static_cast<unsigned char>(c));
    }
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

    Portfolio pf(20000.0);
    pf.print();

    std::string cmd;
        while (true) {
        std::cout << "\n> ";
        std::cin >> cmd;
        if (cmd == "exit") break;
        else if(cmd == "buy"){
            std::string symbol;
            std::string shareStr;
            std::cin >> symbol >> shareStr;

            toupper(symbol);

            std::vector<PriceRecord> prices = md.getPrices(symbol);
            int shares = std::atoi(shareStr.c_str());
            if (prices.empty()|| shares == 0){
                std::cerr << "Symbol not exist or in valid shares" << std::endl;
                continue;
            }
            
            pf.buy(symbol, shares, prices.front().close);
        }
        else if (cmd == "show") {
            pf.print();
        }
        else {
            std::cout << "Commands: buy [symbol] [shares], sell [symbol] [shares], show, exit\n";
        }
    }

    return 0;
}
