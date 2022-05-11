#include "customer.hpp"

// Init to 0 is unnecessary, because static
// variables are automatically initialized to 0
int Customer::id_generator; // = 0;

Customer::Customer(){
    ID = id_generator;
    id_generator++;
}

Customer::~Customer(){
    
}

int Customer::getID() const {
    return ID;
}