#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "customer.hpp"
#include "order_list.hpp"

using namespace std;

class Shop{
private:
    int ID;
    static int id_generator;

    string name;
    vector<int> magazine;
    vector<int> sent_order_IDs;
    OrderList pending_orders;

public:
    Shop( string name );
    Shop( const Shop& archetype );
    ~Shop();

    string getName() const;
    void setName( string new_name );

    void printMagazine() const;
    bool findItem( int item_ID ) const;
    bool addItem( int item_ID );
    bool removeItem( int item_ID );

    bool sendOrder( int order_ID );

    Shop& operator=( const Shop& shop );

    void print() const;

    friend ostream& operator<<( ostream& out, const Shop& shop );
};

#endif /* _SHOP_HPP_ */