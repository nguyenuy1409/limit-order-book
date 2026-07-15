#include "OrderBook.hpp"
#include <iostream>

// Function to get the best bid and best ask
std::pair<int, int> OrderBook::getTopOfBook() {
    if(bids.empty() || asks.empty()) {
        return {-1 , 0};
    }
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
    match();
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

void OrderBook::match() {
    auto bbo = getTopOfBook();
    int bestBid = bbo.first;
    int bestAsk = bbo.second;
    while(bestBid >= bestAsk) {
        int bestBidQuantity = (bids.begin()->second).getFront().getQuantity();
        int bestAskQuantity = (asks.begin()->second).getFront().getQuantity();

        if(bestBidQuantity > bestAskQuantity) {
            bestBidQuantity-=bestAskQuantity;
            bids[bestBid].getFront().reduceQuantity(bestAskQuantity);
            bestAskQuantity = 0;
            asks[bestAsk].pricePop();
            if(asks[bestAsk].isEmpty()) {
                asks.erase(bestAsk);
            }
        }
        else if(bestBidQuantity < bestAskQuantity) {
            bestAskQuantity-=bestBidQuantity;
            asks[bestAsk].getFront().reduceQuantity(bestBidQuantity);
            bestBidQuantity = 0;
            bids[bestBid].pricePop();
            if(bids[bestBid].isEmpty()) {
                bids.erase(bestBid);
            }
        }
        else {
            bestBidQuantity = 0;
            bestAskQuantity = 0;
            (bids.begin()->second).pricePop();
            if(bids[bestBid].isEmpty()) {
                bids.erase(bestBid);
            }
            (asks.begin()->second).pricePop();
            if(asks[bestAsk].isEmpty()) {
                asks.erase(bestAsk);
            }
        }
        bbo = getTopOfBook();
        bestBid = bbo.first;
        bestAsk = bbo.second;
    }
}

int OrderBook::getBestBidQuantity() {
    return (bids.begin()->second).getFront().getQuantity();
}

int OrderBook::getBestAskQuantity() {
    return (asks.begin()->second).getFront().getQuantity();
}