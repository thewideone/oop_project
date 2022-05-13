#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <iostream>
#include <vector>
#include <utility>

#include "customer.hpp"
#include "item.hpp"

using namespace std;

class Order{
private:
    int ID;
    static int ID_generator;    // static variables are 
                                // automatically initialized to 0
    Customer* customer; // pointer to the customer making the order
    bool is_paid;
    
public:
    vector<pair<Item, int>> items;

    Order();
    Order( const Order& other );  // copy constructor
    ~Order();

    int getID() const;
    int getItemCount() const;
    Customer* getCustomer() const;    // returns pointer to the customer
    int isPaid() const;

    // void setPaid( bool state );
    void setCustomer( Customer* customer );

    void addItem( Item& item, int count );
    void removeAllItems();

    void print() const;

    Order& operator=( const Order& order );
    bool operator==( const Order& order ) const;
    bool operator!=( const Order& order ) const;

    friend ostream& operator<<( ostream& out, const Order& order );
};

#endif /* _ORDER_HPP_ */