#ifndef TRADE_H
#define TRADE_H

#include "Order.h"

/**
 * Info about particular order that was involved into the trade
 */
struct TradeInfo {
    OrderID order_id;
    Price price_;
    Quantity quantity;
};

/**
 * Definition for the trade that happened
 */
class Trade {

public:

    Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade) :
        bidTrade_ { bidTrade },
        askTrade_ { askTrade }
    { }

    const TradeInfo& getBidTrade () const;
    const TradeInfo& getAskTrade () const;

private:
    TradeInfo bidTrade_;
    TradeInfo askTrade_;
};

#endif //TRADE_H
