#ifndef _ORDER_LIST_HPP_
#define _ORDER_LIST_HPP_

#include <iostream>
#include <vector>

#include "order.hpp"

using namespace std;

class OrderList{
private:
    vector<Order> orders;

public:
    OrderList();
    OrderList( const OrderList& archetype );
    ~OrderList();

    bool addElement( const Order& order );
    bool removeElement( int order_ID );
    bool removeAllElements();

    int findIndex( int order_ID ) const;    // returns index of an order of
                                            // given ID in "orders" vector

    OrderList& operator=( const OrderList& order_list );
    int operator==( const OrderList& order_list ) const;
    int operator!=( const OrderList& order_list ) const;

    void print() const;

    friend ostream& operator<<( ostream& out, const OrderList& order_list );
};

#endif /* _ORDER_LIST_HPP_ */