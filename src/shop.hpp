#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <iostream>
#include <string>
#include <vector>

class Customer;
class OrderList;

#include "customer.hpp"
#include "order_list.hpp"
#include "item.hpp"

using namespace std;

class Shop {
private:
    int ID;
    static int ID_generator;

    string name;
    //       item ID, item count
    vector<pair<Item,int>> magazine;
    // OrderList* order_history;
    OrderList* pending_orders;

    bool findOrder( int order_ID, int& idx ) const;

public:
    Shop( string name );
    Shop( const Shop& other );
    ~Shop();

    string getName() const;
    void setName( string new_name );
    float getOrderPrice( int order_ID ) const;  // returns price of found order or -1.0 if not found

    // void printMagazine() const;
    // Magazine operations:
    void addItem( Item& item, int count );
    // bool removeItem( int item_ID );                  // returns 0 if item was not found
    bool findItem( int item_ID, int& idx ) const;       // idx is the index of the found item, -1 if not found
    bool removeItemFromMagazine( int item_ID, Item& item, int count );// returns 0 if item was not found
    void removeAllItems();

    int newOrder( Customer* customer );     // returns ID of a newly created order
    bool addItemToOrder( int order_ID, int item_ID, int count );
    bool receivePayment( int order_ID, float money_amount );    // returns true if payment was successful
    // bool sendOrder( int order_ID, string date_of_shipment );
    bool sendOrder( int order_ID );

    Shop& operator=( const Shop& shop );

    void print() const;

    friend ostream& operator<<( ostream& out, const Shop& shop );
};

#endif /* _SHOP_HPP_ */