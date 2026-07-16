cmake_minimum_required(VERSION 3.30)
project(LimitOrderBook)

set(CMAKE_CXX_STANDARD 17)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(LimitOrderBook 
    src/main.cpp
    src/OrderBook.cpp
    src/PriceLevel.cpp
    src/Order.cpp
)

target_include_directories(LimitOrderBook PRIVATE include)

# For tests
add_executable(tests
    tests/OrderBookTest.cpp
    src/OrderBook.cpp
    src/PriceLevel.cpp
    src/Order.cpp
)

target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest_main)

# Google Benchmark
FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(benchmarks
    benchmarks/OrderBookBenchmark.cpp
    src/OrderBook.cpp
    src/PriceLevel.cpp
    src/Order.cpp
)

target_include_directories(benchmarks PRIVATE include)
target_link_libraries(benchmarks benchmark::benchmark)