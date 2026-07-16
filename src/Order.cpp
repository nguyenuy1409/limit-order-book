#include "Order.hpp"

std::string Order::getSide() {
    return side;
}
int Order::getPrice() {
    return price;
}
std::string Order::getOrderId() {
    return order_id;
}
void Order::markCancelled() {
    isCancelled = true;
}
int Order::getQuantity() {
    return quantity;
}
void Order::reduceQuantity(int amount) {
    quantity-=amount;
}