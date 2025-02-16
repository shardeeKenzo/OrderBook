#ifndef TRADINGSYSTEM_H
#define TRADINGSYSTEM_H

#include <utility>

#include "OrderBook.h"
#include "MatchingEngine.h"
#include "Trade.h"

/**
 * Definition for trading system. It connects order book and matching engine so specific matching engine can properly operate on external order book.
 */
class TradingSystem {
public:
    TradingSystem(OrderBook order_book, const MatchingEngine& matching_engine) : order_book_ {std::move(order_book)},
    matching_engine_ {matching_engine}
    {}

    /**
     * Call for the trading system to place an order
     */
    Trades systemPlaceOrder(Price price, Quantity quantity, Side side, OrderType type);
    /**
     * Call for the trading system to modify an order
     */
    Trades systemOrderModify(OrderID order_id, Price price, Quantity quantity, OrderType type);
    /**
     * Call for the trading system to delete an order
     */
    Trades systemDeleteOrder(OrderID order_id);

    OrderBook getOrderBook() const;
    MatchingEngine getMatchingEngine() const;

private:
    OrderBook order_book_;
    MatchingEngine matching_engine_;
};

#endif //TRADINGSYSTEM_H
