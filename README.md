Order Matching Engine

A simple C++ order book that matches buy and sell orders.

Features
Add buy and sell orders
Orders match automatically (best price first, then earliest arrival)
Cancel an order by ID
Print the order book
Build and Run
bash
g++ -std=c++17 -o orderbook main.cpp
./orderbook
Example
cpp
receiveOrder({101, 1, 10, 100, 1});  // Sell 10 @ 100
receiveOrder({201, 0, 15, 110, 2});  // Buy 15 @ 110 -> trade
displayBook();
