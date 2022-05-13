#include "order_list.hpp"

OrderList::OrderList(){

}

OrderList::OrderList( const OrderList& other ){
    orders = other.orders;
}

OrderList::~OrderList(){
    orders.clear();
}

bool OrderList::is_empty() const {
    return orders.empty();
}

void OrderList::addElement( const Order& order ){
    orders.push_back( order );
}

// OrderList& OrderList::operator=( const OrderList& other ){
//     // Check for self-assignment
//     if( this == &other )
//         return *this;
    
//     removeAllElements();
//     orders.reserve( other.orders.size() );
//     orders = other.orders;
//     return *this;
// }

bool OrderList::findElement( int order_ID, int& idx ) const {
    idx = -1;
    for( long long unsigned int i=0; i < orders.size(); i++ )
        if( orders[i].getID() == order_ID ){
            idx = order_ID;
            return true;
        }
    
    return false;
}

// int OrderList::findIndex( int order_ID ) const {
//     int idx = -1;
//     if( findElement( order_ID, idx ) )
//         return idx;
//     return 
// }

bool OrderList::removeElement( int order_ID ){
    int idx = -1;

    if( findElement( order_ID, idx ) ){
        orders.erase( orders.begin() + idx );
        return true;
    }

    return false;
}

void OrderList::removeAllElements(){
    orders.clear();
}

OrderList& OrderList::operator=( const OrderList& other ){
    orders = other.orders;
    return *this;
}

ostream& operator<<( ostream& out, const OrderList& list ){
    for( long long unsigned int i=0; i < list.orders.size(); i++ )
        out << list.orders[i];
    return out;
}