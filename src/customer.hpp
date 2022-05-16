#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <iostream>
#include <vector>
#include <utility>

#include "order.hpp"
#include "order_list.hpp"
#include "shop.hpp"
#include "item.hpp"
class Shop;
class Order;

using namespace std;


class Customer{
private:
    int ID;
    static int ID_generator; // static variables are
                             // automatically initialized to 0

    // struct shop_orders{
    //     vector<int> IDs;
    // };

    //    shop pointer, list of IDs of orders
    // vector< pair<Shop*, vector<int>> > pending_orders;
    OrderList* pending_orders;
    // vector<int> collected_order_IDs;
    OrderList* order_history;    // list of already filled orders

    vector< pair<Item, int> > inventory; // items in the possession of the customer and their count

    // void copyAllPendingOrders( const Customer& other );
    bool addToPendingOrders( const Shop& shop, const Order& order );

public:
    Customer();
    Customer( const Customer& other );
    ~Customer();
    int getID() const;

    void addItemToInventory( Item& item, int count );
    void addOrderToHistory( Order& order );
    void removeOrderFromPending( int order_ID );    // remove an order of given ID from the list of pending orders

    int makeOrder( Shop& shop );    // returns ID of a newly created order
    bool addItemToOrder( Shop& shop, int order_ID, const Item& item, int count );

    bool payForOrder( Shop& shop, int order_ID, float money_amount );

    // void addCollectedOrderID( int order_ID );

    void printInventory();

    Customer& operator=( const Customer& other );
    bool operator==( const Customer& other ) const;
    bool operator!=( const Customer& other ) const;

    // void printPendingOrders() const;
    // void printCollectedOrders() const;
    // void print() const;

    friend ostream& operator<<( ostream& out, const Customer& customer );
};

#endif /* _CUSTOMER_HPP_ */