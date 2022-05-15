#include "shop.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Shop::ID_generator;    // = 0;

Shop::Shop( string name ){
    ID = ID_generator;
    ID_generator++;
    this->name = name;
    pending_orders = new OrderList;
    // order_history = new OrderList;

    cout << "Shop " << name << " has been created" << endl;
}

Shop::Shop( const Shop& other ){
    ID = other.ID;
    name = other.name;
    magazine = other.magazine;
    // order_history = other.order_history;
    pending_orders = other.pending_orders;

    cout << "Shop " << name << " has been created using copy constructor" << endl;
}

Shop::~Shop(){
    removeAllItems();
    delete pending_orders;
    // delete order_history;
}

string Shop::getName() const {
    return name;
}

float Shop::getOrderPrice( int order_ID ) const {
    int order_idx = -1;

    cout << "Shop " << name << ": ";

    if( findOrder( order_ID, order_idx ) )
        return pending_orders->orders[order_idx].getTotalPrice();
    
    return -1.0;
}

void Shop::addItem( Item& item, int count ){
    int idx = -1;
    if( findItem( item.getID(), idx ) ) // if the item already exists,
        magazine[idx].second += count;  // increase its quantity in magazine
    else
        magazine.push_back( make_pair(item, count) );
    
}

// bool Shop::removeItem( int item_ID ){
//     int idx=-1;

//     if( findItem( item_ID, idx ) ){
//         magazine.erase( magazine.begin() + idx );

//         return true;
//     }

//     return false;
// }

void Shop::removeAllItems(){
    magazine.clear();
}

bool Shop::findItem( int item_ID, int& idx ) const {
    idx = -1;
    cout << "Shop " << name << ": ";
    for( long long unsigned int i=0; i < magazine.size(); i++ )
        if( magazine[i].first.getID() == item_ID ){
            idx = i;
            cout << "Found item of ID " << item_ID << endl;
            return true;
        }
    cout << "Item of ID " << item_ID << " not found" << endl;
    return false;
}

bool Shop::removeItemFromMagazine( int item_ID, Item& item, int count ){
    int idx=-1;
    int ret_val = false;

    if( findItem( item_ID, idx ) ){
        if( magazine[idx].second >= count ){
            item = magazine[idx].first;
            magazine[idx].second -= count;
            ret_val = true;
        }
        else
            cout << "Could not remove item of ID " << item_ID << " from magazine: not enough quantity" << endl;
        
        if( magazine[idx].second == 0 )
            // removeItem( item_ID );
            magazine.erase( magazine.begin() + idx );
    }
    else
        cout << "Could not remove item " << item_ID << " from magazine: the item was not found" << endl;

    return ret_val;
}

int Shop::newOrder( Customer* customer ){
    Order order;
    order.setCustomer( customer );

    int order_ID = order.getID();
    pending_orders->addElement( order );

    return order_ID;
}

bool Shop::findOrder( int order_ID, int& idx ) const {
    idx = -1;
    return pending_orders->findElement( order_ID, idx );
}

bool Shop::addItemToOrder( int order_ID, int item_ID, int count ){
    int order_idx = -1;
    bool ret_val = false;

    cout << "Shop " << name << ": ";

    if( findOrder( order_ID, order_idx ) ){
        int item_idx = -1;
        if( findItem( item_ID, item_idx ) ){
            // cout << "Found order and item\n";
            // cout << "Trying to add item " << item_idx << " to order " << order_idx << endl;
            cout << "=====BLABLABLA====\n";
            // cout << "mag size: " << magazine.size();
            // cout << "item_idx: " << item_idx;
            // Item item = magazine[0].first;
            // cout << magazine[0].first.getPrice();
            pending_orders->orders[order_idx].addItem( magazine[item_idx].first, count );

            cout << "Item of ID " << item_ID << " was successufully added to order of ID " << order_ID << endl;
            ret_val = true;
        }
        else
            cout << "No item of ID " << item_ID << " was found in order of ID " << order_ID << endl;
    }
    else
        cout << "No order of ID " << order_ID << " was found" << endl;
    
    return ret_val;
}

// bool Shop::sendOrder( int order_ID, string date_of_shipment ){
bool Shop::sendOrder( int order_ID ){
    bool ret_val = false;
    int order_idx = -1;

    if( findOrder( order_ID, order_idx ) ){
        if( pending_orders->orders[order_idx].isPaid() ){
            for( long long unsigned int i=0; i < pending_orders->orders[order_idx].items.size(); i++ ){
                Item item = pending_orders->orders[order_idx].items[i].first;
                int count = pending_orders->orders[order_idx].items[i].second;

                ret_val = removeItemFromMagazine( item.getID(), item, count );
                // If item was found and removed from magazine, add it to the customer's inventory
                if ( ret_val ){
                    Customer* customer = pending_orders->orders[order_idx].getCustomer();
                    customer->addItemToInventory( item, count );
                }
                else
                    cout << "Shop " << name << ": " << "In order of ID " << order_ID << ": item of ID" << item.getID() << " will not be included in parcel. Reason: invalid quantity" << endl;
            }
            // Set date of shipment of the order
            // pending_orders->orders[order_idx].setDateOfShipment( date_of_shipment );
            // Add the order to histories of orders of the shop and the customer
            Order order = pending_orders->orders[order_idx];
            // order_history->addElement( order );
            // pending_orders->orders[order_idx].getCustomer()->addOrderToHistory( order );
            // Remove the order from pending order list of the shop
            pending_orders->removeElement( order_ID );
            cout << "Shop " << name << ": " << "Order " << order_ID << " was sent successufully" << endl;
        }
        else
            cout << "Shop " << name << ": order of ID " << order_ID << " was not sent, because it has not been paid yet" << endl;
    }
    else
        cout << "Shop " << name << ": could not send order " << order_ID << ": the order was not found" << endl;
    return ret_val;
}

bool Shop::receivePayment( int order_ID, float money_amount ){
    bool ret_val = false;
    int idx = -1;

    cout << "Shop " << name << ": ";

    if( findOrder( order_ID, idx ) ){
        cout << "Shop " << name << ": ";
        if( money_amount == pending_orders->orders[idx].getTotalPrice() ){
            pending_orders->orders[idx].setPaid();
            cout << "Successufully paid for order " << order_ID << endl;
        }
        else if ( money_amount > pending_orders->orders[idx].getTotalPrice() )
            cout << "Customer of ID " << pending_orders->orders[idx].getCustomer()->getID()
                 << " tries to pay too much for order of ID " << pending_orders->orders[idx].getID()
                 << " in shop " << name << endl;
        else
            cout << "Customer of ID " << pending_orders->orders[idx].getCustomer()->getID()
                 << " tries to pay too little for order of ID " << pending_orders->orders[idx].getID()
                 << " in shop " << name << endl;
    }
    else
        cout << "Couldn't pay for order of ID " << order_ID << ": the order does not exist in shop " << name << endl;

    return ret_val;
}

void Shop::print() const {
    cout << *this;
}

ostream& operator<<( ostream& out, const Shop& shop ){
    out << "--------------------" << endl;
    out << "Shop \"" << shop.name << "\" (ID: " << shop.ID << "):" << endl;
    out << "Magazine:" << endl;
    for( long long unsigned int i=0; i < shop.magazine.size(); i++ ){
        out << shop.magazine[i].first;
        out << "\tQuantity: " << shop.magazine[i].second << endl;
    }

    out << "Sent orders:" << endl;
    // if( shop.order_history->is_empty() )
    //     out << "Empty" << endl;
    // else{
    //     out << shop.order_history->orders[0];
    //     for( long long unsigned int i=1; i < shop.order_history->orders.size(); i++ )
    //         out << ", " << shop.order_history->orders[i];
    //     out << endl;
    // }

    out << "Pending orders:" << endl;
    if( shop.pending_orders->is_empty() )
        out << "Empty" << endl;
    else
        out << *shop.pending_orders << endl;
    
    return out;
}