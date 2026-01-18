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
        double lastWkClose = prices[i-7].close;
        double tdyClose = p.close;
        if(i >= 7 && (tdyClose - lastWkClose)/ lastWkClose <= -0.05){
            int shares = portfolio.buyMax(symbol,p.close);
           if(shares > 0){
                history.record({p.date, symbol, "BUY", shares, p.close, portfolio.getCash()});
           }
        }
        else if(i >= 7 && (tdyClose - lastWkClose)/ lastWkClose >= 0.1){
            int shares = portfolio.sellMax(symbol,p.close);
            if(shares > 0){
                history.record({p.date, symbol, "SELL", shares, p.close, portfolio.getCash()});
           }
        }
        
    }

    history.print();
    history.saveCSV("trade_history.csv");
}

Simulator* Simulator::simulator_= nullptr;

Simulator *Simulator::GetInstance(MarketData& md, Portfolio& pf, TradeHistory& th){
    if(simulator_==nullptr){
        simulator_ = new Simulator(md,pf,th);
    }
    return simulator_;
}


