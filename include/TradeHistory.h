#pragma once
#include "TradeRecord.h"
#include <vector>
#include <string>

class TradeHistory {
private:
    std::vector<TradeRecord> history;
public:
    void record(const TradeRecord& trade);
    void print() const;
    void saveCSV(const std::string& filepath) const;
};
