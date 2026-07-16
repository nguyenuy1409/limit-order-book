#include <benchmark/benchmark.h>
#include "OrderBook.hpp"
#include <string>

// Benchmark: inserting a single order that does not match anything
static void BM_InsertNonMatchingOrder(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming(); // don't measure setup
        OrderBook book;
        state.ResumeTiming(); // resume measuring here

        Order bid("001", "AAPL", 100, "limit", "bid", 100, "day");
        book.insert(bid);
    }
}
BENCHMARK(BM_InsertNonMatchingOrder);

// Benchmark: inserting many orders at different price levels (stresses std::map)
static void BM_InsertManyPriceLevels(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        OrderBook book;
        state.ResumeTiming();

        for (int i = 0; i < state.range(0); i++) {
            Order bid(std::to_string(i), "AAPL", 100, "limit", "bid", 100 + i, "day");
            book.insert(bid);
        }
    }
}
BENCHMARK(BM_InsertManyPriceLevels)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_MAIN();