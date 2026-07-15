#include "PriceLevel.hpp"

void PriceLevel::addOrder(Order& order) {
    priceLevel.push(order);
}
Order& PriceLevel::getFront() {
    return priceLevel.front();
}
void PriceLevel::pricePop() {
    priceLevel.pop();
}
bool PriceLevel::isEmpty() {
    return priceLevel.empty();
}