#include "MatchingEngine.h"

#include <iostream>

#include "OrderBook.h"


Quantity MatchingEngine::getTotalLiquidityBelowPrice(OrderBook& order_book, const Price price) const
{
    Quantity total_liquidity { };

    if (auto it = order_book.getAsks().lower_bound(price); it != order_book.getAsks().end())
    {
        while (it != order_book.getAsks().end())
        {
            for (const auto& dq = it->second; const auto& order : dq)
            {
                total_liquidity += order->getRemainingQuantity();
            }
            ++it;
        }
    }
    return total_liquidity;
}

Quantity MatchingEngine::getTotalLiquidityAbovePrice(OrderBook& order_book, const Price price) const
{
    Quantity total_liquidity { };

    if (auto it = order_book.getBids().upper_bound(price); it != order_book.getBids().end())
    {
        while (it != order_book.getBids().end())
        {
            for (const auto& dq = it->second; const auto& order : dq)
            {
                total_liquidity += order->getRemainingQuantity();
            }
            ++it;
        }
    }
    return total_liquidity;
}

Trades MatchingEngine::matchOrders(OrderBook& order_book)
{
    Trades trades;
    trades.reserve(order_book.getOrderDictionary().size());

    while (true)
    {
        if (order_book.getBids().empty() || order_book.getAsks().empty())
        {
            break;
        }

        auto& [bidPrice, bids] = *order_book.getBids().begin();
        auto& [askPrice, asks] = *order_book.getAsks().begin();

        if (bidPrice < askPrice)
        {
            break;
        }

        while (!bids.empty() && !asks.empty())
        {
            const auto bestBid = order_book.getBestBid();
            const auto bestAsk = order_book.getBestAsk();

            const Quantity tradeQuantity = std::min(bestAsk->getRemainingQuantity(), bestBid->getRemainingQuantity());

            bestBid->Fill(tradeQuantity);
            bestAsk->Fill(tradeQuantity);

            if (bestBid->isFilled())
            {
                order_book.deleteOrder(bestBid->getID());
            }
            if (bestAsk->isFilled())
            {
                order_book.deleteOrder(bestAsk->getID());
            }
            trades.push_back(Trade{{bestBid->getID(), bestBid->getPrice(), tradeQuantity},{bestAsk->getID(),bestAsk->getPrice(),tradeQuantity}});
        }
    }
    return trades;
}

bool MatchingEngine::canMatch(OrderBook& order_book, const Side side, const Price price, const OrderType type, const Quantity quantity) const
{

    if (type == OrderType::FillOrKill)
    {
        if (side == Side::Buy)
        {
            if (getTotalLiquidityBelowPrice(order_book, price) < quantity)
            {
                std::cout << "No liquidity for this order" << '\n';
                return false;
            }
        } else
        {
            if (getTotalLiquidityAbovePrice(order_book, price) < quantity)
            {
                std::cout << "No liquidity for this order" << '\n';
                return false;
            }
        }
    }

    if (side == Side::Buy)
    {
        if (order_book.getAsks().empty())
        {
            return false;
        }
        const auto bestAsk = order_book.getBestAsk();

        return price >= bestAsk->getPrice();
    }
    else
    {
        if (order_book.getBids().empty())
        {
            return false;
        }
        const auto bestBid = order_book.getBestBid();

        return price <= bestBid->getPrice();
    }
}
