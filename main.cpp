#include <deque>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using Quantity = size_t;
using Price = double;
using OrderID = size_t;

enum class Side
{
    Buy,
    Sell,
};

enum class OrderType
{
    Market,
    GoodTillCancel,
    FillAndKill,
};

class Order
{
private:
    OrderID id_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
    Side side_;
    OrderType type_;

public:
    Order(const OrderID id, const Price price, const Quantity quantity, const Side side, const OrderType type) :
    id_ { id },
    price_ { price } ,
    initialQuantity_ { quantity } ,
    remainingQuantity_ { quantity },
    side_ { side },
    type_ { type }
    {}

    OrderID getID() const { return id_; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return initialQuantity_; }
    Quantity getRemainingQuantity() const { return remainingQuantity_; }
    Side getSide() const { return side_; }
    OrderType getType() const { return type_; }
    Quantity getFilledQuantity() const { return initialQuantity_ - remainingQuantity_; }

    bool isFilled() const
    {
        return remainingQuantity_ == 0;
    }

    void Fill(const Quantity quantity)
    {
        if (quantity > remainingQuantity_)
        {
            throw std::logic_error(std::format("Insufficient quantity at {}'s order", id_));
        }

        remainingQuantity_ -= quantity;
    }

};

using OrderDictionary = std::vector<std::shared_ptr<Order>>;

class OrderBook
{
private:
    OrderID counter = 0;

    std::multimap<Price, std::deque<std::shared_ptr<Order>>, std::greater<>> buys { };
    std::multimap<Price, std::deque<std::shared_ptr<Order>>, std::less<>> bids { };

    OrderDictionary order_dictionary {};

public:

    OrderBook() = default;

    std::shared_ptr<Order> orderPlace(Price price, Quantity quantity, Side side, OrderType type)
    {
        auto order = std::make_shared<Order>(++counter,price,quantity,side,type);
        order_dictionary.push_back(order);

        if (order->getSide() == Side::Buy)
        {
            if (const auto it = buys.find(order->getPrice()); it == buys.end())
            {
                buys.insert({order->getPrice(), std::deque{order}});
            } else
            {
                it->second.push_back(order);
            }
        }
        if (order->getSide() == Side::Sell)
        {
            if (const auto it = bids.find(order->getPrice()); it == bids.end())
            {
                bids.insert({order->getPrice(), std::deque{order}});
            } else
            {
                it->second.push_back(order);
            }
        }
        return order;
    }

    void orderDelete(OrderID order_id)
    {
        const auto it = std::ranges::find_if(order_dictionary, [order_id] (const std::shared_ptr<Order>& order)
        {
            return order->getID() == order_id;
        });

        if (it == order_dictionary.end())
        {
            throw std::invalid_argument("Order does not exist");
            return;
        }
        const auto& order = *it;

        order_dictionary.erase(it);

        if (order->getSide() == Side::Buy)
        {
            const auto mapsIt = buys.find(order->getPrice());
            auto& dq = mapsIt->second;
            std::erase(dq, order);

            if (dq.empty())
            {
                buys.erase(mapsIt);
            }
        } else
        {
            const auto mapsIt = bids.find(order->getPrice());
            auto& dq = mapsIt->second;
            std::erase(dq, order);

            if (dq.empty())
            {
                bids.erase(mapsIt);
            }
        }

    }

    void printQuantityAtLevel(const Price price)
    {
        if (const auto it = buys.find(price); it == buys.end())
        {
            std::cout << "No orders on this price" << std::endl;
            return;
        } else
        {
            Quantity quan = 0;
            for (const auto orders = it->second; const auto& order : orders)
            {
                std::cout << std::format("Order {} with quantity {}", order->getID(), order->getQuantity()) << std::endl;
                quan += order->getQuantity();
            }
            std::cout << "Total quantity is " << quan << std::endl;
        }
    }
};




int main()
{
    OrderBook order_book {};

    order_book.orderPlace(15, 100, Side::Buy, OrderType::GoodTillCancel);
    order_book.orderPlace(15, 80, Side::Buy, OrderType::GoodTillCancel);
    order_book.orderPlace(15, 30, Side::Buy, OrderType::GoodTillCancel);

    order_book.printQuantityAtLevel(15);

    order_book.orderDelete(1);

    order_book.printQuantityAtLevel(15);
    return 0;
}

