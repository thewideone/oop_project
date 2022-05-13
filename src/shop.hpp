#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <iostream>
#include <string>
#include <vector>

// #include "customer.hpp"
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
    vector<int> sent_order_IDs;
    OrderList pending_orders;

    // bool findOrder( int order_ID, int& idx ) const;

public:
    Shop( string name );
    Shop( const Shop& other );
    ~Shop();

    string getName() const;
    void setName( string new_name );

    // void printMagazine() const;
    // Magazine operations:
    void addItem( Item& item, int count );
    bool removeItem( int item_ID );                 // returns 0 if item was not found
    bool findItem( int item_ID, int& idx ) const;   // idx is the index of the found item, -1 if not found
    bool sellItem( int item_ID, Item& item, int count );    // returns 0 if item was not found
    // bool takeItem( int item_ID, Item& item );       // returns 0 if item was not found
    void removeAllItems();

    // void newOrder( Customer* customer, int& order_ID ); // assigns ID of newly created order to "order_ID"
    // bool addItemToOrder( int order_ID, int item_ID, int count );
    bool sendOrder( int order_ID );

    Shop& operator=( const Shop& shop );

    void print() const;

    friend ostream& operator<<( ostream& out, const Shop& shop );
};

#endif /* _SHOP_HPP_ */