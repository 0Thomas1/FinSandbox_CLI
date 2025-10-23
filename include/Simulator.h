#pragma once
#include "MarketData.h"
#include "Portfolio.h"
#include "TradeHistory.h"

class Simulator {
private:
    MarketData& marketData;
    Portfolio& portfolio;
    TradeHistory& history;
public:
    Simulator(MarketData& md, Portfolio& pf, TradeHistory& th);
    void run(const std::string& symbol, int startIdx, int endIdx);
};
