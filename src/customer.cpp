#include "customer.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Customer::ID_generator; // = 0;

Customer::Customer(){
    ID = ID_generator;
    ID_generator++;

    order_history = new OrderList;

    cout << "Customer " << ID << " has been created" << endl;
}

Customer::Customer( const Customer& other ){
    ID = other.ID;
    copyAllPendingOrders( other );
    collected_order_IDs.clear();
    collected_order_IDs.reserve( other.collected_order_IDs.size() );
    collected_order_IDs = other.collected_order_IDs;
    inventory = other.inventory;

    order_history->orders = other.order_history->orders;

    cout << "Customer " << ID << " has been created  using copy constructor" << endl;
}

Customer::~Customer(){
    pending_orders.clear();
    collected_order_IDs.clear();
    delete order_history;
}

int Customer::getID() const {
    return ID;
}

void Customer::addItemToInventory( Item& item, int count ){
    if( count <= 0 ){
        cerr << "In Customer::addItemToInventory(): Invalid item quantity. Ignoring." << endl;
        return;
    }

    inventory.push_back( make_pair( item, count ) );
}

void Customer::addOrderToHistory( Order& order ){
    order_history->addElement( order );
}

int Customer::makeOrder( Shop& shop ){
    int order_ID = shop.newOrder( this );
    return order_ID;
}

bool Customer::addItemToOrder( Shop& shop, int order_ID, int item_ID, int count ){
    if( count <= 0 ){
        cerr << "In Customer::addItemToOrder(): Invalid item quantity. Ignoring." << endl;
        return false;
    }

    return shop.addItemToOrder( order_ID, item_ID, count );
}

void Customer::copyAllPendingOrders( const Customer& other ){
    pending_orders.clear();
    pending_orders.reserve( other.pending_orders.size() );

    for( long long unsigned int i=0; i < other.pending_orders.size(); i++ ){
        pending_orders[i].first  = other.pending_orders[i].first;
        pending_orders[i].second = other.pending_orders[i].second;
    }
}

bool Customer::payForOrder( Shop& shop, int order_ID, float money_amount ){
    if( money_amount <= 0 ){
        cerr << "In Customer::payForOrder(): Invalid item quantity. Ignoring." << endl;
        return false;
    }
    return shop.receivePayment( order_ID, money_amount );
}

// void Customer::addCollectedOrderID( int order_ID ){
//     collected_order_IDs.push_back( order_ID );
// }

void Customer::printInventory(){
    cout << "--------------------" << endl;
    cout << "Customer " << ID << ": inventory:" << endl;
    for( long long unsigned int i=0; i < inventory.size(); i++ )
        cout << inventory[i].first << "\tQuantity: " << inventory[i].second << endl;
}

Customer& Customer::operator=( const Customer& other ){
    if( this == &other )
        return *this;
    
    ID = other.ID;
    copyAllPendingOrders( other );
    collected_order_IDs.clear();
    collected_order_IDs.reserve( other.collected_order_IDs.size() );
    collected_order_IDs = other.collected_order_IDs;

    return *this;
}

bool Customer::operator==( const Customer& other ) const {
    if( this == &other )
        return true;
    
    if( ID == other.ID ){
        for( long long unsigned int i=0; i < other.collected_order_IDs.size(); i++ )
            if( collected_order_IDs[i] != other.collected_order_IDs[i] )
                return false;
        for( long long unsigned int i=0; i < other.pending_orders.size(); i++ )
            if( pending_orders[i].second != other.pending_orders[i].second )
                return false;
    }

    return true;
}

bool Customer::operator!=( const Customer& other ) const {
    return !( *this == other );
}

ostream& operator<<( ostream& out, const Customer& customer ){
    out << "--------------------" << endl;
    out << "Customer " << customer.ID << ":" << endl;

    out << "Inventory:" << endl;
    for( long long unsigned int i=0; i < customer.inventory.size(); i++ )
        cout << customer.inventory[i].first << "\tQuantity: " << customer.inventory[i].second << endl;

    long long unsigned int shop_count = customer.pending_orders.size();

    for( long long unsigned int i=0; i < shop_count; i++ ){
        int shop_ID = customer.pending_orders[i].first;
        long long unsigned int order_count = customer.pending_orders[i].second.size();

        out << "\tIDs of pending orders in shop " << shop_ID << " (" << order_count << " in total):" << endl;
        out << "\t\t";

        if( customer.pending_orders[i].second.empty() )
            out << "Empty";
        else {
            out << customer.pending_orders[i].second[0];
            for( long long unsigned int order_ID=1; order_ID < order_count; order_ID++ )
                out << ", " << customer.pending_orders[i].second[order_ID];
        }
        out << endl;
    }

    long long unsigned int collected_order_cnt = customer.collected_order_IDs.size();

    out << "\tIDs of collected orders: ";

    if( customer.collected_order_IDs.empty() )
            out << "Empty";
    else{
        out << customer.collected_order_IDs[0];
        for( long long unsigned int i=0; i < collected_order_cnt; i++ )
            out << ", " << customer.collected_order_IDs[i];
    }

    out << endl;

    out << "Order history:" << endl;
    if( customer.order_history->is_empty() )
        out << "Empty" << endl;
    else
        out << *customer.order_history;
    

    return out;
}