#include "OrderBook.h"

#include <iostream>

void OrderBook::placeOrder(Price price, Quantity quantity, Side side, OrderType type)
{

    const auto order = std::make_shared<Order>(++counter,price,quantity,side,type);
    order_dictionary.emplace(order->getID(), order);

    if (order->getSide() == Side::Buy)
    {
        if (const auto it = bids_.find(order->getPrice()); it == bids_.end())
        {
            bids_.insert({order->getPrice(), std::deque{order}});
        } else
        {
            it->second.push_back(order);
        }
    }
    if (order->getSide() == Side::Sell)
    {
        if (const auto it = asks_.find(order->getPrice()); it == asks_.end())
        {
            asks_.insert({order->getPrice(), std::deque{order}});
        } else
        {
            it->second.push_back(order);
        }
    }
}

void OrderBook::deleteOrder(OrderID order_id)
{
    if (!order_dictionary.contains(order_id))
    {
        throw std::invalid_argument(std::format("Order {} does not exist", order_id));
    }

    const auto order = order_dictionary[order_id];

    order_dictionary.erase(order_id);

    if (order->getSide() == Side::Buy)
    {
        const auto mapsIt = bids_.find(order->getPrice());
        auto& dq = mapsIt->second;
        std::erase(dq, order);

        if (dq.empty())
        {
            bids_.erase(mapsIt);
        }
    } else
    {
        const auto mapsIt = asks_.find(order->getPrice());
        auto& dq = mapsIt->second;
        std::erase(dq, order);

        if (dq.empty())
        {
            asks_.erase(mapsIt);
        }
    }
}

void OrderBook::modifyOrder(OrderID order_id, const Price price, const Quantity quantity, const OrderType type)
{
    if (!order_dictionary.contains(order_id))
    {
        throw std::invalid_argument(std::format("Order {} does not exist", order_id));
    }

    bool shouldBeReinserted = false;

    const auto& order = order_dictionary[order_id];

    if (price != order->getPrice() || type != order->getType())
    {
        shouldBeReinserted = true;
        deleteOrder(order_id);

    }

    order->setPrice(price);
    order->setQuantity(quantity);
    order->setType(type);

    if (shouldBeReinserted)
    {
        placeOrder(price, quantity, order->getSide(), type);
    }
}

std::shared_ptr<Order> OrderBook::getBestAsk() const
{
    if (asks_.empty())
    {
        return nullptr;
    }

    const auto& bestAsk = *asks_.begin();

    return bestAsk.second.front();
}

std::shared_ptr<Order> OrderBook::getBestBid() const
{
    if (bids_.empty())
    {
        return nullptr;
    }

    const auto& bestBid = *bids_.begin();

    return bestBid.second.front();
}

const OrderDictionary& OrderBook::getOrderDictionary() const
{
    return order_dictionary;
}

std::map<Price, std::deque<std::shared_ptr<Order>>, std::greater<>>& OrderBook::getBids()
{
    return bids_;
}

std::map<Price, std::deque<std::shared_ptr<Order>>, std::less<>>& OrderBook::getAsks()
{
    return asks_;
}

void OrderBook::printQuantityAtLevelBids(const Price price) const
{
    if (const auto it = bids_.find(price); it == bids_.end())
    {
        std::cout << "No orders on this price" << std::endl;
    } else
    {
        Quantity quan = 0;
        for (const auto orders = it->second; const auto& order : orders)
        {
            std::cout << std::format("Order {} with quantity {}", order->getID(), order->getRemainingQuantity()) << std::endl;
            quan += order->getRemainingQuantity();
        }
        std::cout << "Total quantity is " << quan << std::endl;
    }
}

void OrderBook::printQuantityAtLevelAsks(const Price price) const
{
    if (const auto it = asks_.find(price); it == asks_.end())
    {
        std::cout << "No orders on this price" << std::endl;
    } else
    {
        Quantity quan = 0;
        for (const auto orders = it->second; const auto& order : orders)
        {
            std::cout << std::format("Order {} with quantity {}", order->getID(), order->getRemainingQuantity()) << std::endl;
            quan += order->getRemainingQuantity();
        }
        std::cout << "Total quantity is " << quan << std::endl;
    }
}

void OrderBook::printDictionary() const
{
    for (const auto& order : order_dictionary)
    {
        std::cout << order.second->getID() << std::endl;
    }
}