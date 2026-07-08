#pragma once
#include <map>
#include <functional>
#include <utility>
#include "PriceLevel.hpp"
#include "Order.hpp"

class OrderBook {
private:
    std::map<int, PriceLevel> asks;
    std::map<int, PriceLevel, std::greater<int>> bids;
public:
    std::pair<int, int> getTopOfBook();
    void insert(Order& order);
    void cancel(std::string order_id);
    void modify(Order& order);
};