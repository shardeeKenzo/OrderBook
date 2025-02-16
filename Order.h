#ifndef ORDER_H
#define ORDER_H
#include <format>

using Quantity = size_t;
using Price = double;
using OrderID = size_t;



/**
 *  Define side of the order
 */
enum class Side
{
    Buy,
    Sell,
};

/**
 *  Define order type
 */
enum class OrderType
{
    GoodTillCancel,
    FillOrKill,
    ImmediateOrCancel,
};

/**
 *  Definition of the order
 */
class Order
{
public:
    Order(const OrderID id, const Price price, const Quantity quantity, const Side side, const OrderType type) :
    id_ { id },
    price_ { price } ,
    initialQuantity_ { quantity } ,
    remainingQuantity_ { quantity },
    side_ { side },
    type_ { type }
    {}

    OrderID getID() const;
    Price getPrice() const;
    /**
    *  Return the quantity that the order had in the very beginning
    */
    Quantity getInitialQuantity() const;
    /**
    *  Return the quantity that the order has right now
    */
    Quantity getRemainingQuantity() const;
    Side getSide() const;
    OrderType getType() const;
    Quantity getFilledQuantity() const;

    void setPrice (Price price);
    void setQuantity(Quantity quantity);
    void setType(OrderType type);

    /**
    *  Check if the order was fully filled
    */
    bool isFilled() const;
    /**
    *  Fills the order with provided quantity
    */
    void Fill(Quantity quantity);

private:
    OrderID id_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
    Side side_;
    OrderType type_;
};

#endif //ORDER_H
