#pragma once
#include <queue>
#include "Order.hpp"

class PriceLevel {
private:
    int price;
    std::queue<Order> priceLevel;
public:
    PriceLevel(int price) {
        this->price = price;
    }
};