#pragma once
#include <string>

class Order {
private:
    std::string order_id;
    std::string instrument;
    int quantity;
    std::string order_type;
    std::string side;
    int price;
    std::string time_in_force;
    bool isCancelled;

public:
    Order() : isCancelled(false) {}
    Order(std::string order_id, std::string instrument, int quantity, std::string order_type, std::string side, int price, std::string time_in_force) {
        this->order_id = order_id;
        this->instrument = instrument;
        this->quantity = quantity;
        this->order_type = order_type;
        this->side = side;
        this->price = price;
        this->time_in_force = time_in_force;
        this->isCancelled = false;
    }

    std::string getSide() {
        return side;
    }
    int getPrice() {
        return price;
    }
    std::string getOrderId() {
        return order_id;
    }
    void markCancelled() {
        isCancelled = true;
    }
    int getQuantity() {
        return quantity;
    }
    void reduceQuantity(int amount) {
        quantity-=amount;
    }
};