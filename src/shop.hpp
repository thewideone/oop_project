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
#include "order.hpp"

class Order;

using namespace std;

class Shop {
private:
    int ID;
    static int ID_generator;

    string name;
    //       item ID, item count
    vector<pair<Item,int>> magazine;    // list of items and their counts
    OrderList* pending_orders;
    OrderList* order_history;

    bool findPendingOrder( int order_ID, int& idx ) const;
    bool findHistoryOrder( int order_ID, int& idx ) const;

public:
    Shop( string name );
    Shop( const Shop& other );
    ~Shop();

    string getName() const;
    void setName( string new_name );
    bool getOrder( int order_ID, Order& order ) const;  // returns true if the order of given ID was found
                                                        // and assigns a copy of the order to "order" parameter
    float getOrderPrice( int order_ID ) const;          // returns price of found order or -1.0 if not found

    // Magazine operations:
    void addItem( Item& item, int count );
    // bool removeItem( int item_ID );                  // returns 0 if item was not found
    bool findItem( int item_ID, int& idx ) const;       // idx is the index of the found item, -1 if not found
    bool removeItemFromMagazine( int item_ID, Item& item, int count ); // returns 0 if item was not found
    bool removeItemFromMagazine( int item_ID, int count );
    bool removeItemFromMagazine( Item& item, int count );
    bool removeItemFromMagazine( int item_ID ); // remove all items of this ID
    bool removeItemFromMagazine( Item& item );  // remove all items of this ID
    void removeAllItems(); 

    int newOrder( Customer* customer );     // returns ID of a newly created order
    bool addItemToOrder( int order_ID, int item_ID, int count );
    bool receivePayment( int order_ID, float money_amount );    // returns true if payment was successful
    bool sendOrder( int order_ID, string date_of_shipment );

    Shop& operator=( const Shop& shop );

    void print() const;

    friend ostream& operator<<( ostream& out, const Shop& shop );
};

#endif /* _SHOP_HPP_ */