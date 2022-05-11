#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

#include <iostream>
#include <vector>

using namespace std;


class Customer{
private:
    int ID;
    static int id_generator; // static variables are // automatically initialized to 0

    struct shop_orders{
        vector<int> IDs;
    };

    vector<shop_orders> pending_orders;
    vector<int> collected_order_IDs;
public:
    Customer();
    Customer( const Customer& archetype );
    ~Customer();
    int getID() const;

    Customer& operator=( const Customer& customer );
    int operator==( const Customer& customer ) const;
    int operator!=( const Customer& customer ) const;

    void printPendingOrders() const;
    void printCollectedOrders() const;
    void print() const;

    friend ostream& operator<<( ostream& out, const Customer& customer );
};

#endif /* _CUSTOMER_HPP_ */