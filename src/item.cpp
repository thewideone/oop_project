#include "item.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Item::ID_generator;    // = 0;

Item::Item( float price, int exp_date ){
    ID = ID_generator;
    ID_generator++;

    this->price = price;
    expiration_date = exp_date;

    dout << "Item " << ID << " has been created" << endl;
}

Item::Item( const Item& other ){
    ID = other.ID;
    price = other.price;
    expiration_date = other.expiration_date;

    dout << "Item " << ID << " has been created by copy constructor" << endl;
}

int Item::getID() const {
    return ID;
}

float Item::getPrice() const {
    return price;
}

int Item::getExiprationDate() const {
    return expiration_date;
}

bool Item::setPrice( float new_price ){
    if( new_price <= 0 )
        return false;
    
    price = new_price;

    return true;
}

bool Item::setExiprationDate( int new_date ){
    if( new_date <= 0 )
        return false;
    
    expiration_date = new_date;

    return true;
}

Item& Item::operator=( const Item& other ){
    if( this == &other )
        return *this;
    
    ID = other.ID;
    price = other.price;
    expiration_date = other.expiration_date;

    return *this;
}

bool Item::operator==( const Item& other ) const {
    if( this == &other )
        return true;
    if( ID == other.ID &&
        price == other.price &&
        expiration_date == other.expiration_date )
        return true;
    return false;
}

bool Item::operator!=( const Item& other ) const {
    return !(*this == other);
}

ostream& operator<<( ostream& out, const Item& item ){
    out << "Item " << item.ID << ":" << endl;
    out << "\tPrice: " << item.price << endl;
    out << "\tExpiration date: " << item.expiration_date << endl;

    return out;
}