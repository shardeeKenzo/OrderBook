cmake_minimum_required(VERSION 3.30)
project(BasicOrderBook)

set(CMAKE_CXX_STANDARD 26)

# Configure Boost preferences
set(Boost_USE_STATIC_LIBS        ON)  # Use shared libraries
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

set(BOOST_ROOT "C:/MyStuff/C++ Projects/libraries/boost_1_87_0_install")

find_package(Boost 1.86 REQUIRED COMPONENTS system)

if(Boost_FOUND)
    # Create your executable target (adjust the source file as needed)
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

    # Add Boost's include directories to your target
    target_include_directories(BasicOrderBook PRIVATE ${Boost_INCLUDE_DIRS})

    # Link the Boost libraries (e.g., Boost.System)
    target_link_libraries(BasicOrderBook PRIVATE ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Boost!")
endif()

