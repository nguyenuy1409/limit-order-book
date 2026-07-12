#include "OrderBook.hpp"
#include "PriceLevel.hpp"

// Function to get the best bid and best ask
std::pair<int, int> OrderBook::getTopOfBook() {
    int bestBid = bids.begin()->first;
    int bestAsk = asks.begin()->first;
    return {bestBid, bestAsk};
}

// Function to insert order to the order book
void OrderBook::insert(Order& order) {
    if(order.getSide() == "bid") {
        bids[order.getPrice()].addOrder(order);
    }
    else {
        asks[order.getPrice()].addOrder(order);
    }
}


// Function to cancel order
void OrderBook::cancel(std::string order_id) {
    if(cancelledOrders.count(order_id) == 0) {
        cancelledOrders[order_id] = true;
    } 
}

// Function to modify order
void OrderBook::modify(Order& order) {
    cancel(order.getOrderId());
    insert(order);
}