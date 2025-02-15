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

class OrderBook
{
public:

    OrderBook() = default;

    void placeOrder(Price price, Quantity quantity, Side side, OrderType type);
    void deleteOrder(OrderID order_id);
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
    OrderID counter = 0;

    std::map<Price, std::deque<std::shared_ptr<Order>>, std::greater<>> bids_ { };
    std::map<Price, std::deque<std::shared_ptr<Order>>, std::less<>> asks_ { };

    OrderDictionary order_dictionary {};
};



#endif //ORDERBOOK_H
