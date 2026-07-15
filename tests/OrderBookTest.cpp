#include <gtest/gtest.h>
#include "OrderBook.hpp"

TEST(OrderBookTest, InsertBidOrder) {
    Order bid("001", "Nuke", 67, "limit", "bid", 69, "day");
    OrderBook book;
    book.insert(bid);
    EXPECT_EQ(book.getBestBidQuantity(), 67);
}

TEST(OrderBookTest, InsertAskOrder) {
    Order ask("002", "Nuke", 96, "limit", "ask", 69, "day");
    OrderBook book;
    book.insert(ask);
    EXPECT_EQ(book.getBestAskQuantity(), 96);
}

TEST(OrderBookTest, MatchingEngine) {
    Order bid("001", "Nuke", 67, "limit", "bid", 69, "day");
    Order ask("002", "Nuke", 67, "limit", "ask", 69, "day");
    OrderBook book;
    book.insert(bid);
    book.insert(ask);
    EXPECT_EQ(book.getTopOfBook().first, -1);
    EXPECT_EQ(book.getTopOfBook().second, 0);
}