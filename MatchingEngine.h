#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include <vector>
#include "OrderBook.h"
#include "Trade.h"

/**
 * Definition of matching engine
 */
class MatchingEngine {
public:

    MatchingEngine() = default;

    /**
     *  Checks if there is a match between two orders
     */
    bool canMatch(OrderBook& order_book, Side side, Price price, OrderType type, Quantity quantity) const;
    /**
     * Get total liquidity below specific price
     */
    Quantity getTotalLiquidityBelowPrice(OrderBook& order_book, Price price) const;
    /**
     * Get total liquidity above specific price
     */
    Quantity getTotalLiquidityAbovePrice(OrderBook& order_book, Price price) const;
    /**
     * Matching orders in the order book
     */
    Trades matchOrders(OrderBook& order_book);
};
#endif //MATCHINGENGINE_H
