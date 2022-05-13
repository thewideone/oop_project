#include "shop.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Shop::ID_generator;    // = 0;

Shop::Shop( string name ){
    ID = ID_generator;
    ID_generator++;
    this->name = name;
}

Shop::Shop( const Shop& other ){
    ID = other.ID;
    name = other.name;
    magazine = other.magazine;
    sent_order_IDs = other.sent_order_IDs;
    pending_orders = other.pending_orders;
}

Shop::~Shop(){
    removeAllItems();
}

void Shop::addItem( Item& item, int count ){
    magazine.push_back( make_pair(item, count) );
}

bool Shop::removeItem( int item_ID ){
    int idx=-1;

    if( findItem( item_ID, idx ) ){
        magazine.erase( magazine.begin() + idx );

        return true;
    }

    return false;
}

void Shop::removeAllItems(){
    magazine.clear();
}

bool Shop::findItem( int ID, int& idx ) const {
    idx = -1;
    for( long long unsigned int i=0; i < magazine.size(); i++ )
        if( magazine[i].first.getID() == ID ){
            idx = i;
            return true;
        }
    return false;
}

bool Shop::sellItem( int item_ID, Item& item, int count ){
    int idx=-1;
    int ret_val = false;

    if( findItem( item_ID, idx ) ){
        if( magazine[idx].second >= count ){
            item = magazine[idx].first;
            magazine[idx].second -= count;
            ret_val = true;
        }
        else
            cout << "Not enough quantity of item in magazine" << endl;
        if( magazine[idx].second == 0 )
            removeItem( item_ID );
    }

    return ret_val;
}

// void Shop::newOrder( Customer* customer, int &order_ID ){
//     Order order( customer );
//     order_ID = order.getID();
//     pending_orders.addElement( order );
// }

// bool Shop::findOrder( int order_ID, int& idx ) const {
//     idx = -1;
//     return pending_orders.findElement( order_ID, idx );
// }

// bool Shop::addItemToOrder( int order_ID, int item_ID, int count ){
//     int order_idx = -1;
//     if( findOrder( order_ID, order_idx ) ){
//         int item_idx = -1;
//         if( findItem( item_ID, item_idx ) ){
//             Item item = magazine[item_idx].first;
//             pending_orders.orders[order_idx].addItem( item, count );
//         }
//     }
// }

void Shop::print() const {
    cout << *this;
}

ostream& operator<<( ostream& out, const Shop& shop ){
    out << "--------------------" << endl;
    out << "Shop \"" << shop.name << "\" (ID: " << shop.ID << "):" << endl;
    out << "Magazine:" << endl;
    for( long long unsigned int i=0; i < shop.magazine.size(); i++ ){
        out << shop.magazine[i].first;
        out << "\tCount: " << shop.magazine[i].second << endl;
    }

    out << "Sent order IDs: ";
    if( shop.sent_order_IDs.empty() )
        out << "Empty" << endl;
    else{
        out << shop.sent_order_IDs[0];
        for( long long unsigned int i=0; i < shop.sent_order_IDs.size(); i++ )
            out << ", " << shop.sent_order_IDs[i];
        out << endl;
    }

    out << "Pending orders:" << endl;
    if( shop.pending_orders.is_empty() )
        out << "Empty" << endl;
    else
        out << shop.pending_orders << endl;

    out << "--------------------" << endl;
    
    return out;
}