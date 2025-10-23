#pragma once
#include <string>

struct TradeRecord {
    std::string date;
    std::string symbol;
    std::string action;  // "BUY" or "SELL"
    int shares;
    double price;
    double cashAfter;
};
