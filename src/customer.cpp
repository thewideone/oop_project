#include "customer.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Customer::ID_generator; // = 0;

Customer::Customer(){
    ID = ID_generator;
    ID_generator++;

    pending_orders = new OrderList;
    order_history = new OrderList;

    dout << "Customer " << ID << " has been created" << endl;
}

Customer::Customer( const Customer& other ){
    ID = other.ID;
    inventory.reserve( other.inventory.size() );
    inventory = other.inventory;
    pending_orders = new OrderList( *other.pending_orders );
    order_history = new OrderList( *other.order_history );

    dout << "Customer " << ID << " has been created by copy constructor" << endl;
}

Customer::~Customer(){
    delete pending_orders;
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

    // Add a copy newly created order in the shop
    // to pending order list of the customer
    Order order;
    if( shop.getOrder( order_ID, order ) )
        addOrderToPending( order );
    
    return order_ID;
}

void Customer::addOrderToPending( Order& order ){
    pending_orders->addElement( order );
}

void Customer::removeOrderFromPending( int order_ID ){
    pending_orders->removeElement( order_ID );
}

bool Customer::addItemToOrder( Shop& shop, int order_ID, const Item& item, int count ){
    if( count <= 0 ){
        cerr << "In Customer::addItemToOrder(): Invalid item quantity. Ignoring." << endl;
        return false;
    }

    int item_ID = item.getID();

    bool ret_val = shop.addItemToOrder( order_ID, item_ID, count );

    // If the item was added to the order in the shop,
    // update the order in the customer's pending order list,
    // that is copy the order from the shop to the customer's pending order list
    if( ret_val ){
        int order_idx = -1;
        if( pending_orders->findElement( order_ID, order_idx ) ){
            Order order;
            if( shop.getOrder( order_ID, order ) )
                pending_orders->orders[order_idx] = order;
            else
                ret_val = false;
        }
        else
            ret_val = false;
    }

    return ret_val;
}

bool Customer::payForOrder( Shop& shop, int order_ID, float money_amount ){
    if( money_amount <= 0 ){
        cerr << "In Customer::payForOrder(): Invalid item quantity. Ignoring." << endl;
        return false;
    }

    bool ret_val = shop.receivePayment( order_ID, money_amount );

    // If shop has received the payment
    if( ret_val ){
        // Find the same order in pending order list
        // and set its "is_paid" flag to true
        int order_idx = -1;
        if( pending_orders->findElement( order_ID, order_idx ) )
            pending_orders->orders[order_idx].setPaid();
        else{
            cerr << "In Customer::payForOrder(): Customer " << ID << ": Order " << order_ID << " not found" << endl;
            ret_val = false;
        }
    }
    else{
        cerr << "In Customer::payForOrder(): Customer " << ID << " could not pay for order " << order_ID << endl;
        ret_val = false;
    }

    return ret_val;
}

Customer& Customer::operator=( const Customer& other ){
    if( this == &other )
        return *this;
    
    ID = other.ID;
    inventory.clear();
    inventory.reserve( other.inventory.size() );
    inventory = other.inventory;

    pending_orders->orders.clear();
    delete pending_orders;
    pending_orders = new OrderList(*other.pending_orders);

    order_history->orders.clear();
    delete order_history;
    order_history = new OrderList(*other.order_history);

    return *this;
}

bool Customer::operator==( const Customer& other ) const {
    if( this == &other )
        return true;
    
    if( ID == other.ID &&
        *pending_orders == *other.pending_orders &&
        *order_history == *other.order_history &&
        inventory == other.inventory )
        return true;
    return false;
}

bool Customer::operator!=( const Customer& other ) const {
    return !( *this == other );
}

void Customer::printInventory() const {
    cout << "--------------------" << endl;
    cout << "Customer " << ID << ": inventory:" << endl;
    for( long long unsigned int i=0; i < inventory.size(); i++ )
        cout << inventory[i].first << "\tQuantity: " << inventory[i].second << endl;
}

void Customer::printPendingOrders() const {
    cout << "Pending orders of customer " << ID << ":";
    if( pending_orders->is_empty() )
        cout << " None" << endl;
    else
        cout << endl << *pending_orders;
}

void Customer::printCollectedOrders() const {
    cout << "Collected orders of customer " << ID << ":";
    if( order_history->is_empty() )
        cout << " None" << endl;
    else
        cout << endl << *order_history;
}

ostream& operator<<( ostream& out, const Customer& customer ){
    out << "--------------------" << endl;
    out << "Customer " << customer.ID << ":" << endl;

    out << "Inventory:" << endl;
    for( long long unsigned int i=0; i < customer.inventory.size(); i++ )
        out << customer.inventory[i].first << "\tQuantity: " << customer.inventory[i].second << endl;
    
    out << "Pending orders:";
    if( customer.pending_orders->is_empty() )
        out << " None" << endl;
    else
        out << endl << *customer.pending_orders;

    // long long unsigned int shop_count = customer.pending_orders.size();
    // out << "shop cnt: " << shop_count << endl;

    // for( long long unsigned int i=0; i < shop_count; i++ ){
    //     int shop_ID = customer.pending_orders[i].first;
    //     long long unsigned int order_count = customer.pending_orders[i].second.size();

    //     out << "\tIDs of pending orders in shop " << shop_ID << " (" << order_count << " in total):" << endl;
    //     out << "\t\t";

    //     if( customer.pending_orders[i].second.empty() )
    //         out << "None";
    //     else {
    //         out << customer.pending_orders[i].second[0];
    //         for( long long unsigned int order_ID=1; order_ID < order_count; order_ID++ )
    //             out << ", " << customer.pending_orders[i].second[order_ID];
    //     }
    //     out << endl;
    // }

    // long long unsigned int collected_order_cnt = customer.collected_order_IDs.size();

    // out << "\tIDs of collected orders: ";

    // if( customer.collected_order_IDs.empty() )
    //         out << "Empty";
    // else{
    //     out << customer.collected_order_IDs[0];
    //     for( long long unsigned int i=0; i < collected_order_cnt; i++ )
    //         out << ", " << customer.collected_order_IDs[i];
    // }

    out << "Collected orders:";
    if( customer.order_history->is_empty() )
        out << " None" << endl;
    else
        out << endl << *customer.order_history;
    

    return out;
}