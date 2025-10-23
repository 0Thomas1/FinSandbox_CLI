#include "Simulator.h"
#include <iostream>
#include <iomanip>

Simulator::Simulator(MarketData& md, Portfolio& pf, TradeHistory& th)
    : marketData(md), portfolio(pf), history(th) {}

void Simulator::run(const std::string& symbol, int startIdx, int endIdx) {
    const std::vector<PriceRecord>& prices = marketData.getPrices(symbol);
    if (prices.empty()) {
        std::cerr << "No data for " << symbol << "\n";
        return;
    }

    startIdx = std::max(0, startIdx);
    endIdx = std::min((int)prices.size() - 1, endIdx);

    std::cout << "\nSimulating " << symbol << " from "
              << prices[endIdx].date << " to " << prices[startIdx].date << "\n";

    for (int i = startIdx; i <= endIdx; i++) { // reverse chronological order
        const auto& p = prices[i];
        std::cout << p.date << " | $" << std::fixed << std::setprecision(2)
                  << p.close << "\n";

        // Simple strategy example:
        // Buy if price drops below $150, sell if above $200
        if(i >= 7 && (prices[i-7].close - p.close)/p.close <= -0.05){
           if(portfolio.buy(symbol,10,p.close)){
                history.record({p.date, symbol, "BUY", 10, p.close, portfolio.getCash()});
           }
        }
        else if(i >= 7 && (prices[i-7].close - p.close)/p.close >= 0.1){
            if(portfolio.sell(symbol,10,p.close)){
                history.record({p.date, symbol, "SELL", 10, p.close, portfolio.getCash()});
           }
        }
        
    }

    history.print();
    history.saveCSV("trade_history.csv");
}
