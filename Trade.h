#ifndef TRADE_H
#define TRADE_H

#include "Order.h"

struct TradeInfo {
    OrderID order_id;
    Price price_;
    Quantity quantity;
};

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
