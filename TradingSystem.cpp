#include "TradingSystem.h"



Trades TradingSystem::systemPlaceOrder(const Price price, const Quantity quantity, const Side side, const OrderType type)
{
    if (type == OrderType::FillOrKill)
    {
        if (!matching_engine_.canMatch(order_book_, side, price, type, quantity))
        {
            return { };
        }
    }
    order_book_.placeOrder(price, quantity, side, type);

    Trades matchTrades = matching_engine_.matchOrders(order_book_);
    return matchTrades;
}
Trades TradingSystem::systemOrderModify(const OrderID order_id, const Price price, const Quantity quantity, const OrderType type)
{
    order_book_.modifyOrder(order_id, price, quantity, type);

    Trades matchTrades = matching_engine_.matchOrders(order_book_);
    return matchTrades;
}
Trades TradingSystem::systemDeleteOrder(const OrderID order_id)
{
    order_book_.deleteOrder(order_id);

    Trades matchTrades = matching_engine_.matchOrders(order_book_);
    return matchTrades;
}