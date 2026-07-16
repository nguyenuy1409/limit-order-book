# Limit Order Book

A C++ implementation of a Limit Order Book (LOB) — the core data structure used by exchanges to match buy and sell orders.

## What is a Limit Order Book?

A Limit Order Book is a data structure that exchanges use to receive limit orders (bids or asks) from traders. These orders rest in the book instead of being executed immediately like market orders. A resting order waits until a matching bid and ask price is found, then it gets executed.

## Order Fields

| Field | Description |
|---|---|
| Order ID | Uniquely identifies each order |
| Instrument | The asset you want to trade |
| Quantity | The amount of the instrument you want to buy or sell |
| Order Type | Limit order or market order |
| Side | Bid (buy) or ask (sell) |
| Price | The price at which you want to trade (limit orders only) |
| Time-in-Force | How long the order remains active (e.g., Day order or Good Till Cancelled) |

## Structure

A Limit Order Book has two sides: the buy side and the sell side. On the buy side, price levels are sorted from highest to lowest. On the sell side, price levels are sorted from lowest to highest. Within each price level, there may be multiple orders. These orders follow price-time priority, where the order placed first gets executed first (FIFO).

### Data Structure Decision

I need a data structure to store orders in the book that automatically sorts them by priority, with highest to lowest for the bid side and lowest to highest for the ask side. I chose `std::map` because it sorts automatically and has O(log N) time complexity for search, insert, and delete.

However, `std::map` is not optimal for low-latency systems because it stores each node at a random location on the heap, which leads to frequent cache misses — every time the CPU needs to access the next node, it has to fetch it from RAM instead of cache, which is significantly slower.

For future improvement, I plan to replace `std::map` with `std::flat_map`, which stores data contiguously in memory like `std::vector`, resulting in better cache locality and lower memory footprint. Though insert and delete in `std::flat_map` are slower than `std::map` because they have to shift elements to maintain sorted order — O(N) time complexity — the search complexity remains O(log N).

## Benchmark Results

Benchmarked using Google Benchmark on Windows (MinGW-W64, Debug build). The benchmark measures the time to insert N orders at N different price levels into a `std::map`-based `OrderBook`, forcing the map to create a new tree node for each insertion.

<img width="1284" height="279" alt="image" src="https://github.com/user-attachments/assets/815ac8df-5123-48a1-a6ce-06903bc1d562" />
<p align="center"><em>Raw output from Google Benchmark</em></p>

The time roughly scales linearly with the number of orders (~10x time for ~10x orders), which is consistent with `std::map`'s O(log N) insert complexity — the log N factor grows slowly compared to N, so the dominant cost is proportional to N.

This is the baseline before optimization. The next step is to switch to `std::flat_map` to reduce cache misses from `std::map`'s scattered heap allocations, then re-run this benchmark to measure the improvement.

## Matching Engine

Two orders are matched when the bid price is greater than or equal to the ask price. The execution price is determined by the resting order — the order that arrived first becomes the maker and sets the price, while the incoming order is the taker. If the incoming order cannot be fully filled by a single resting order, it will continue matching against the next orders in the queue. This is called a partial fill.

## Operations

| Operation | Description |
|---|---|
| `insert()` | Adds a limit order to the book when it is not executed immediately |
| `modify()` | Changes order information such as quantity or price |
| `cancel()` | Removes a specific order from the book |
| `getTopOfBook()` | Returns the current best bid and ask prices (BBO — Best Bid Offer) |
