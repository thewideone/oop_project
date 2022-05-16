#include "order_list.hpp"

OrderList::OrderList(){
    dout << "OrderList has been created" << endl;
}

OrderList::OrderList( const OrderList& other ){
    orders = other.orders;
    dout << "OrderList has been created using copy constructor" << endl;
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

bool OrderList::findElement( int order_ID, int& idx ) const {
    idx = -1;

    dout << "OrderList: ";

    for( long long unsigned int i=0; i < orders.size(); i++ )
        if( orders[i].getID() == order_ID ){
            idx = i;
            dout << "Found order of ID " << order_ID << " at index " << idx << endl;
            return true;
        }

    dout << "Order of ID " << order_ID << " not found" << endl;

    return false;
}

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
    // Check for self-assignment
    if( this == &other )
        return *this;
    
    removeAllElements();
    orders.reserve( other.orders.size() );
    orders = other.orders;
    return *this;
}

bool OrderList::operator==( const OrderList& other ) const {
    // Check for self-assignment
    if( this == &other )
        return true;

    if( orders == other.orders )
        return true;
    return false;
}

bool OrderList::operator!=( const OrderList& other ) const {
    return !(*this == other);
}

ostream& operator<<( ostream& out, const OrderList& order_list ){
    for( long long unsigned int i=0; i < order_list.orders.size(); i++ )
        out << order_list.orders[i];
    return out;
}