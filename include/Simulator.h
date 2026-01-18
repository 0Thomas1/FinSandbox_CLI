#pragma once
#include "MarketData.h"
#include "Portfolio.h"
#include "TradeHistory.h"

class Simulator {
private:
    MarketData& marketData;
    Portfolio& portfolio;
    TradeHistory& history;
    static Simulator* simulator_;
    Simulator(MarketData& md, Portfolio& pf, TradeHistory& th);
public:
    //Simulator(MarketData& md, Portfolio& pf, TradeHistory& th);
    void run(const std::string& symbol, int startIdx, int endIdx);
    Simulator (Simulator& other) = delete;
    void operator=(const Simulator &) = delete;
    static Simulator *GetInstance(MarketData& md, Portfolio& pf, TradeHistory& th);



};
