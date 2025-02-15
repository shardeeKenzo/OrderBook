#include "TradingSystem.h"

int main()
{
    constexpr MatchingEngine matching_engine{};
    const OrderBook order_book {};

    TradingSystem trading_system {order_book, matching_engine };

    trading_system.systemPlaceOrder(15, 100, Side::Buy, OrderType::GoodTillCancel);
    trading_system.systemPlaceOrder(15, 100, Side::Buy, OrderType::GoodTillCancel);
    trading_system.systemPlaceOrder(15, 100, Side::Buy, OrderType::GoodTillCancel);



    trading_system.systemPlaceOrder(15, 500, Side::Sell, OrderType::FillOrKill);
    trading_system.systemPlaceOrder(15, 10, Side::Sell, OrderType::GoodTillCancel);
    trading_system.systemPlaceOrder(15, 50, Side::Sell, OrderType::GoodTillCancel);
    trading_system.systemPlaceOrder(15, 300, Side::Sell, OrderType::GoodTillCancel);

    trading_system.getOrderBook().printDictionary();
    trading_system.getOrderBook().printQuantityAtLevelAsks(15);

    return 0;
}

