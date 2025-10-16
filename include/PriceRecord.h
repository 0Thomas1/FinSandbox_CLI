#pragma once
#include <string>
struct PriceRecord {
    std::string date;
    double open, high, low, close;
    long volume;
    double adjustedClose;   // optional (Yahoo provides this)
    std::string symbol;     // optional, if multiple assets
};