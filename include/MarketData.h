#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "PriceRecord.h"

class MarketData {
private:
    std::unordered_map<std::string, std::vector<PriceRecord>> data;
public:
    void loadCSV(const std::string& symbol, const std::string& filepath);
    void loadFromAPI(const std::string& symbol, const std::string& apiKey);
    const std::vector<PriceRecord>& getPrices(const std::string& symbol) const;
};
