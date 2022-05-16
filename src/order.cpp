#include "order.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Order::ID_generator;    // = 0;

Order::Order(){
    ID = ID_generator;
    ID_generator++;

    customer = nullptr;
    is_paid = 0;
    date_of_shipment = "";
    shop_name = "";

    dout << "Order " << ID << " has been created." << endl;
}

Order::Order( const Order& other ){
    ID = other.ID;
    customer = other.customer;
    is_paid = other.is_paid;
    date_of_shipment = other.date_of_shipment;
    shop_name = other.shop_name;
    items = other.items;

    dout << "Order " << ID << " has been created by copy constructor." << endl;
}

Order::~Order(){
    removeAllItems();
    dout << "Order " << ID << " has been deleted." << endl;
}

int Order::getID() const {
    return ID;
}

int Order::getItemCount() const {
    return items.size();
}

Customer* Order::getCustomer() const {
    return customer;
}

bool Order::isPaid() const {
    return is_paid;
}
void Order::setPaid(){
    is_paid = true;
}

float Order::getTotalPrice() const {
    float sum = 0.0;

    for( long long unsigned int i=0; i < items.size(); i++ )
        sum += items[i].first.getPrice() * items[i].second;
    
    return sum;
}

void Order::setDateOfShipment( string date ){
    date_of_shipment = date;
}
string Order::getDateOfShipment() const {
    return date_of_shipment;
}

void Order::setShopName( string name ){
    shop_name = name;
}
string Order::getShopName() const {
    return shop_name;
}

void Order::addItem( Item item, int count ){
    items.push_back( make_pair( item, count ) );
}

void Order::removeAllItems(){
    items.clear();
}

void Order::setCustomer( Customer* customer ){
    this->customer = customer;
}

void Order::print() const {
    cout << *this;
}

Order& Order::operator=( const Order& other ){
    // Check for self-assignment
    if( this == &other )
        return *this;
    
    ID = other.ID;
    customer = other.customer;
    is_paid = other.is_paid;
    shop_name = other.shop_name;
    date_of_shipment = other.date_of_shipment;

    removeAllItems();
    items.reserve( other.items.size() );
    items = other.items;

    return *this;
}

bool Order::operator==( const Order& order ) const {
    if( this == &order )
        return true;
    
    if ( items.size() == order.items.size() &&
        is_paid  == order.isPaid() ){
        for( long long unsigned int i=0; i < items.size(); i++ )
            if( items[i].first  != order.items[i].first || 
                items[i].second != order.items[i].second  )
                return false;
    }

    return true;
}

bool Order::operator!=( const Order& order ) const {
    return !(*this == order);
}

ostream& operator<<( ostream& out, const Order& order ){
    out << "Order " << order.getID() << ":" << endl;

    out << "\tCustomer's ID: " << order.getCustomer()->getID() << endl;

    out << "\tPaid: " << (order.is_paid ? "yes" : "no") << endl;

    out << "\tDate of shipment: ";

    if( order.date_of_shipment == "" )
        out << "Not shipped yet" << endl;
    else
        out << order.date_of_shipment << endl;

    long long unsigned int item_cnt = order.items.size();
    long long unsigned int total_item_cnt=0;

    if( order.items.empty() )
        out << "No items" << endl;
    else{
        out << "\t" << item_cnt << " different items:" << endl;

        for( long long unsigned int i=0; i<item_cnt; i++ ){
            out << "\t\tID: " << order.items[i].first.getID() << " | Quantity: " << order.items[i].second << endl;
            total_item_cnt += order.items[i].second;
        }

        out << "\tIn total " << total_item_cnt << " items" << endl;
    }

    return out;
}