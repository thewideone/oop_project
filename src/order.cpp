#include "order.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Order::id_generator;    // = 0;

// Constructor
Order::Order( Customer* customer, int* item_array, int item_count ){
    ID = id_generator;
    id_generator++;

    cust = customer;
    item_cnt = item_count;
    is_paid = 0;

    // items[i][j] -> items[i*item_count+j]
    items = new int[item_count*2];
    

    for( int i=0; i < item_count*2; i++ ){
        items[i] = item_array[i];
    }

    cout << "Order " << ID << " has been created." << endl;
}

// Copy constructor
Order::Order( const Order& order ){
    ID = order.getID();
    cust = order.getCustomer();
    item_cnt = order.getItemCount();
    is_paid = order.isPaid();

    // items[i][j] -> items[i*item_count+j]
    int item_count = order.getItemCount();
    items = new int[item_count*2];
    

    for( int i=0; i < item_count*2; i++ ){
        items[i] = order.items[i];
    }

    cout << "Order " << ID << " has been created by copy constructor." << endl;
}

// Destructor
Order::~Order(){
    cout << "Order " << ID << " has been deleted." << endl;
    removeAllItems();
}

int Order::getID() const {
    return ID;
}
int Order::getItemCount() const {
    return item_cnt;
}
Customer* Order::getCustomer() const {
    return cust;
}
int Order::isPaid() const {
    return is_paid;
}
void Order::print() const {
    cout << *this;
}
bool Order::removeAllItems(){
    delete items;
    item_cnt = 0;
    return true;
}

ostream& operator<<( ostream& out, const Order& order ){
    out << "Order " << order.getID() << ":" << endl;

    out << "\tCustomer's ID: " << order.getCustomer()->getID() << endl;

    int item_cnt = order.getItemCount();

    out << "\tItems (" << item_cnt << ") total:" << endl;

    for( int i=0; i<item_cnt; i++ ){
        out << "\t\tID: " << order.items[ i*item_cnt ] << " | Count: " << order.items[ i*item_cnt+1 ] << endl;
    }

    return out;
}

Order& Order::operator=( const Order& order ){
    // Check for self-assignment
    if( this == &order )
        return *this;
    
    removeAllItems();
    ID = order.getID();
    cust = order.getCustomer();
    item_cnt = order.getItemCount();
    is_paid = order.isPaid();

    items = new int[item_cnt*2];

    for( int i=0; i<item_cnt*2; i++ ){
        items[i] = order.items[i];
    }
    return *this;
}

int Order::operator==( const Order& order ) const {
    if ( item_cnt == order.getItemCount() &&
         is_paid  == order.isPaid() ){
        for( int i=0; i < item_cnt*2; i++ )
            if( items[i] != order.items[i] )
                return false;
    }

    return true;
}

int Order::operator!=( const Order& order ) const {
    return !(*this == order);
}