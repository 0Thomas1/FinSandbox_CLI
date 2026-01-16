#include "MarketData.h"
#include "Portfolio.h"
#include "TradeHistory.h"
#include "Simulator.h"

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
    md.loadFromAPI("ABAT", apiKey);

    Portfolio pf(10000.0);
    TradeHistory th;
    Simulator sim(md, pf, th);

    sim.run("ABAT", 0, 365 * 10);  // simulate over 10 years

    std::cout << "\nFinal Portfolio Value: $"
              << pf.getCash() << " + holdings value\n";
    pf.print();
    return 0;
}

 