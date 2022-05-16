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
    // No private members
public:
    vector<Order> orders;

    OrderList();
    OrderList( const OrderList& other );
    ~OrderList();

    bool is_empty() const;

    void addElement( const Order& order );
    bool removeElement( int order_ID ); // returns true if operation successful
    void removeAllElements();

    // Returns true if element found and its index in "idx"
    bool findElement( int order_ID, int& idx ) const; // idx set to -1 by default

    OrderList& operator=( const OrderList& other );
    bool operator==( const OrderList& other ) const;
    bool operator!=( const OrderList& other ) const;

    // void print() const;

    friend ostream& operator<<( ostream& out, const OrderList& order_list );
};

#endif /* _ORDER_LIST_HPP_ */