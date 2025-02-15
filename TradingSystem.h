#ifndef TRADINGSYSTEM_H
#define TRADINGSYSTEM_H

#include <utility>

#include "OrderBook.h"
#include "MatchingEngine.h"
#include "Trade.h"

class TradingSystem {
public:
    TradingSystem(OrderBook order_book, const MatchingEngine& matching_engine) : order_book_ {std::move(order_book)},
    matching_engine_ {matching_engine}
    {}

    Trades systemPlaceOrder(Price price, Quantity quantity, Side side, OrderType type);
    Trades systemOrderModify(OrderID order_id, Price price, Quantity quantity, OrderType type);
    Trades systemDeleteOrder(OrderID order_id);

    OrderBook getOrderBook() const;
    MatchingEngine getMatchingEngine() const;

private:
    OrderBook order_book_;
    MatchingEngine matching_engine_;
};

#endif //TRADINGSYSTEM_H
