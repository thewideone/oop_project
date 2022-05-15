#ifndef _ORDER_LIST_HPP_
#define _ORDER_LIST_HPP_

#include <iostream>
#include <vector>

#include "order.hpp"
class Order;
// #include "customer.hpp"

// #include "item.hpp"

using namespace std;

class OrderList{
private:
public:
    vector<Order> orders;

    OrderList();
    OrderList( const OrderList& other );
    ~OrderList();

    bool is_empty() const;

    void addElement( const Order& order );
    bool removeElement( int order_ID );
    void removeAllElements();

    bool findElement( int order_ID, int& idx ) const; // idx set to -1 by default
    // int findIndex( int order_ID ) const;    // returns index of an order of
                                            // given ID in "orders" vector

    OrderList& operator=( const OrderList& other );
    // int operator==( const OrderList& other ) const;
    // int operator!=( const OrderList& other ) const;

    // void print() const;

    friend ostream& operator<<( ostream& out, const OrderList& list );
};

#endif /* _ORDER_LIST_HPP_ */