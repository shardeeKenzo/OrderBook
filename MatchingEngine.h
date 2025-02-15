#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include <vector>
#include "OrderBook.h"
#include "Trade.h"

class MatchingEngine {
public:

    MatchingEngine() = default;

    bool canMatch(OrderBook& order_book, Side side, Price price, OrderType type, Quantity quantity);
    Quantity getTotalLiquidityBelowPrice(OrderBook& order_book, Price price);
    Quantity getTotalLiquidityAbovePrice(OrderBook& order_book, Price price);
    Trades matchOrders(OrderBook& order_book);
};
#endif //MATCHINGENGINE_H
