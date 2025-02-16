#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <deque>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Trade.h"

using OrderDictionary = std::unordered_map<OrderID, std::shared_ptr<Order>>;
using Trades = std::vector<Trade>;

/**
 *  Definition of the order book
 */
class OrderBook
{
public:

    OrderBook() = default;

    /**
    *  Place order with following parameters in orderbook and order dictionary
    */
    void placeOrder(Price price, Quantity quantity, Side side, OrderType type);

    /**
    *  Delete order with following id
    */
    void deleteOrder(OrderID order_id);
    /**
    *  Modify order with following parameters
    */
    void modifyOrder(OrderID order_id, Price price, Quantity quantity, OrderType type);

    std::shared_ptr<Order> getBestAsk() const;
    std::shared_ptr<Order> getBestBid() const;
    const OrderDictionary& getOrderDictionary() const;

    void printQuantityAtLevelBids(Price price) const;
    void printQuantityAtLevelAsks(Price price) const;
    void printDictionary() const;

    std::map<Price, std::deque<std::shared_ptr<Order>>, std::greater<>>& getBids();
    std::map<Price, std::deque<std::shared_ptr<Order>>, std::less<>>& getAsks();

private:
    /**
    *  Counter for order id
    */
    OrderID counter = 0;

    std::map<Price, std::deque<std::shared_ptr<Order>>, std::greater<>> bids_ { };
    std::map<Price, std::deque<std::shared_ptr<Order>>, std::less<>> asks_ { };

    OrderDictionary order_dictionary {};
};



#endif //ORDERBOOK_H
