#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <iostream>
#include <vector>

#include "customer.hpp"

using namespace std;

class Order{
private:
    int ID;
    static int id_generator;    // static variables are 
                                // automatically initialized to 0
    
    Customer* cust; // pointer to the customer making the order
    bool is_paid;
    int item_cnt;   // item count
    
public:
    int* items;                 // list of items and their count
                                // items[i][j] is then rewritten as
                                // items[i*item_count+j]

    Order( Customer* customer, int* item_array, int item_count );
    Order( const Order& archetype );  // copy constructor
    ~Order();

    int getID() const;
    int getItemCount() const;
    Customer* getCustomer() const;    // returns pointer to the customer
    int isPaid() const;

    void setPaid( bool state );

    bool removeAllItems();            // returns 1 if succeeded, 0 otherwise

    void print() const;

    Order& operator=( const Order& order );
    int operator==( const Order& order ) const;
    int operator!=( const Order& order ) const;

    friend ostream& operator<<( ostream& out, const Order& order );
};



#endif /* _ORDER_HPP_ */