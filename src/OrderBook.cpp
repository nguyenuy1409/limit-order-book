#include "OrderBook.hpp"

std::pair<int, int> OrderBook::getTopOfBook() {
    int bestBid = bids.begin()->first;
    int bestAsk = asks.begin()->first;
    return {bestBid, bestAsk};
}