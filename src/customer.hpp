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
    static int ID_generator;    // static variables are
                                // automatically initialized to 0

    OrderList* pending_orders;  // list of pending orders
    OrderList* order_history;   // list of already collected orders

    vector< pair<Item, int> > inventory; // items in the possession of the customer and their count

public:
    Customer();
    Customer( const Customer& other );
    ~Customer();
    int getID() const;

    void addItemToInventory( Item& item, int count );
    void addOrderToPending( Order& order );
    void addOrderToHistory( Order& order );
    void removeOrderFromPending( int order_ID );    // remove an order of given ID from the list of pending orders

    int makeOrder( Shop& shop );    // returns ID of a newly created order
    bool addItemToOrder( Shop& shop, int order_ID, const Item& item, int count );   // returns true if operation succeeded

    bool payForOrder( Shop& shop, int order_ID, float money_amount );   // returns true if operation succeeded

    Customer& operator=( const Customer& other );
    bool operator==( const Customer& other ) const;
    bool operator!=( const Customer& other ) const;

    void printInventory() const;
    void printPendingOrders() const;
    void printCollectedOrders() const;

    friend ostream& operator<<( ostream& out, const Customer& customer );
};

#endif /* _CUSTOMER_HPP_ */