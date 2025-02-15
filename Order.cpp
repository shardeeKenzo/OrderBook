#include "Order.h"

OrderID Order::getID() const { return id_; }
Price Order::getPrice() const { return price_; }
Quantity Order::getQuantity() const { return initialQuantity_; }
Quantity Order::getRemainingQuantity() const { return remainingQuantity_; }
Side Order::getSide() const { return side_; }
OrderType Order::getType() const { return type_; }
Quantity Order::getFilledQuantity() const { return initialQuantity_ - remainingQuantity_; }

void Order::setPrice (const Price price) { price_ = price; }
void Order::setQuantity(const Quantity quantity) { initialQuantity_ = quantity; }
void Order::setType(const OrderType type) { type_ = type; }


bool Order::isFilled() const
{
    return remainingQuantity_ == 0;
}

void Order::Fill(const Quantity quantity)
{
    if (quantity > remainingQuantity_)
    {
        throw std::logic_error(std::format("Insufficient quantity at {}'s order", id_));
    }

    remainingQuantity_ -= quantity;
}