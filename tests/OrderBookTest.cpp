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

TEST(OrderBookTest, PartialFill) {
    Order bid("001", "Nuke", 667, "limit", "bid", 69, "day");
    Order ask("002", "Nuke", 67, "limit", "ask", 69, "day");
    OrderBook book;
    book.insert(bid);
    book.insert(ask);
    EXPECT_EQ(book.getBestBidQuantity(), 600);
    EXPECT_EQ(book.getTopOfBook().second, 0);
}

TEST(OrderBookTest, CancelOrder) {
    Order bid("001", "Nuke", 667, "limit", "bid", 69, "day");
    Order ask("002", "Nuke", 67, "limit", "ask", 69, "day");
    OrderBook book;
    book.insert(bid);
    book.cancel(bid.getOrderId());
    book.insert(ask);
    EXPECT_EQ(book.getTopOfBook().first, -1);
    EXPECT_EQ(book.getTopOfBook().second, 0);
}

TEST(OrderBookTest, FIFO_Test) {
    Order bid("001", "Nuke", 70, "limit", "bid", 167, "day");
    Order ask1("002", "Nuke", 670, "limit", "ask", 69, "day");
    Order ask2("003", "Nuke", 690, "limit", "ask", 69, "day");
    OrderBook book;
    book.insert(bid);
    book.insert(ask1);
    book.insert(ask2);
    EXPECT_EQ(book.getBestAskQuantity(), 600);
}