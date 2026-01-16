#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <iomanip>

class Portfolio {
private:
    double cash;
    std::unordered_map<std::string, int> holdings; // symbol → shares
public:
    Portfolio(double initialCash = 10000.0);

    void deposit(double amount);
    bool buy(const std::string& symbol, int shares, double price);
    int buyMax(const std::string& symbol,double price);
    bool sell(const std::string& symbol, int shares, double price);
    int sellMax(const std::string& symbol,double price);

    double getCash() const;
    double getValue(const std::unordered_map<std::string, double>& latestPrices) const;
    void print() const;
};
