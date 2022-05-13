#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <iostream>
#include <vector>
#include <utility>

// #include "shop.hpp"

using namespace std;


class Customer{
private:
    int ID;
    static int ID_generator; // static variables are
                             // automatically initialized to 0

    // struct shop_orders{
    //     vector<int> IDs;
    // };

    //       shop ID, IDs of orders
    vector< pair<int, vector<int>> > pending_orders;
    vector<int> collected_order_IDs;

    void copyAllPendingOrders( const Customer& other );

public:
    Customer();
    Customer( const Customer& other );
    ~Customer();
    int getID() const;

    // // bool makeOrder( const Shop& shop, int &order_ID );
    // // bool addItemToOrder( const Shop& shop, int &order_ID, int item_ID, int count );

    Customer& operator=( const Customer& other );
    bool operator==( const Customer& other ) const;
    bool operator!=( const Customer& other ) const;

    // void printPendingOrders() const;
    // void printCollectedOrders() const;
    // void print() const;

    friend ostream& operator<<( ostream& out, const Customer& customer );
};

#endif /* _CUSTOMER_HPP_ */