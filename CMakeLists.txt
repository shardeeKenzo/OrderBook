cmake_minimum_required(VERSION 3.30)
project(BasicOrderBook)

set(CMAKE_CXX_STANDARD 26)

add_executable(BasicOrderBook main.cpp
        Order.cpp
        Order.h
        Trade.cpp
        Trade.h
        OrderBook.cpp
        OrderBook.h
        MatchingEngine.cpp
        MatchingEngine.h
        TradingSystem.cpp
        TradingSystem.h)
