#pragma once
#include <map>
#include <unordered_map>
#include <functional>
#include <utility>
#include "PriceLevel.hpp"
#include "Order.hpp"

class OrderBook {
private:
    std::map<int, PriceLevel> asks;
    std::map<int, PriceLevel, std::greater<int>> bids;
    std::unordered_map<std::string, bool> cancelledOrders;
    void match();
public:
    std::pair<int, int> getTopOfBook();
    void insert(Order& order);
    void cancel(std::string order_id);
    void modify(Order& order);
};