#include "Portfolio.h"
#include <cmath>

Portfolio::Portfolio(double initialCash) : cash(initialCash) {}

void Portfolio::deposit(double amount) {
    if (amount > 0) {
        cash += amount;
    }
}

bool Portfolio::buy(const std::string& symbol, int shares, double price){
    double cost = shares * price;

    if(cost > cash){
        std::cerr << "Not enough cash to buy " << shares << " shares of " << symbol << "\n";
        return false;
    }
    holdings[symbol] += shares;
    cash -= cost;
    std::cout << "Bought " << symbol << " x" << shares << " at $" << price << "\n";
    return true;
}
int Portfolio::buyMax(const std::string& symbol, double price){
    int shares = floor(cash / price);
    if (buy(symbol,shares,price)){
        return shares;
    }
    return 0;
}
bool Portfolio::sell(const std::string& symbol, int shares, double price) {
    if (holdings[symbol] < shares) {
        std::cerr << "Not enough shares of " << symbol << " to sell.\n";
        return false;
    }
    holdings[symbol] -= shares;
    cash += shares * price;
    std::cout << "Sold " << shares << " shares of " << symbol << " at $" << price << "\n";
    return true;
}
int Portfolio::sellMax(const std::string& symbol, double price){
    int shares = holdings[symbol];
    if (sell(symbol,shares,price)){
        return shares;
    }
    return 0;
}

double Portfolio::getCash() const {
    return cash;
}

double Portfolio::getValue(const std::unordered_map<std::string, double>& latestPrices) const{
    double total = cash;
    for (const auto& [symbol, shares] : holdings) {
        auto it = latestPrices.find(symbol);
        if (it != latestPrices.end()) {
            total += shares * it->second;
        }
    }
    return total;
}

void Portfolio::print() const {
    std::cout << "\n--- Portfolio ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Cash: $" << cash << "\n";
    for (const auto& [symbol, shares] : holdings) {
        std::cout << symbol << ": " << shares << " shares\n";
    }
    std::cout << "-----------------\n";
}