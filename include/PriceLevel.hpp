#pragma once
#include <queue>
#include "Order.hpp"

class PriceLevel {
private:
    int price;
    std::queue<Order> priceLevel;
public:
    // Default constructor
    PriceLevel() : price(0) {}
    // Parameterized constructor
    PriceLevel(int price) {
        this->price = price;
    }

    void addOrder(Order& order) {
        priceLevel.push(order);
    }
};