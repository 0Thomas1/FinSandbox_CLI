#include "TradeHistory.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void TradeHistory::record(const TradeRecord& trade){
    history.push_back(trade);
}

void TradeHistory::print() const {
    std::cout << "\n--- Trade History ---\n";
    for (const TradeRecord& t : history) {
        std::cout << t.date << " | " << std::setw(4) << t.action << " | "
                    << std::setw(5) << t.symbol << " | "
                    << t.shares << " @ $" << t.price
                    << " | Cash: $" << t.cashAfter << "\n";
    }
    std::cout << "----------------------\n";
}

void TradeHistory::saveCSV(const std::string& filepath) const{
    std::ofstream file(filepath);
    file << "date,symbol,action,shares,price,cashAfter\n";
    for (const auto& t : history) {
        file << t.date << "," << t.symbol << "," << t.action << ","
             << t.shares << "," << t.price << "," << t.cashAfter << "\n";
    }
    file.close();
}