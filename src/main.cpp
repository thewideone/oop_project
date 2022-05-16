#include <iostream>

#include "order.hpp"
#include "customer.hpp"
#include "shop.hpp"
#include "order_list.hpp"
#include "item.hpp"

// int main(int argc, char *argv[]){
int main( void ){
	Item i1( 4.20, 1 ), i2( 1.23, 2 );
	// cout<<i1;
	Order o1, o2;
	Customer c1,c2;

	Shop s1("ALABAMA");
	s1.addItem(i1, 10);
	s1.addItem(i1, -15);
	s1.addItem(i2, 102);
	cout << s1;

	int order_ID = c1.makeOrder( s1 );
	cout << "Created order of ID " << order_ID << endl;

	c1.addItemToOrder( s1, order_ID, i1.getID(), 12 );
	c1.addItemToOrder( s1, order_ID, i2.getID(), 100 );
	c1.addItemToOrder( s1, order_ID, i2.getID(), 10 );
	float price = s1.getOrderPrice( order_ID );
	cout << "Order " << order_ID << " price is " << price << endl;
	cout << c1;
	c1.payForOrder( s1, order_ID, price );
	// cout << s1;
	cout << c1;
	s1.sendOrder( order_ID, "15/05/2022" );
	// s1.sendOrder( order_ID );
	// c1.printInventory();

	cout << s1;
	cout << c1;

	
	// Order o5;
	// o5.setCustomer(&c1);
	// o5.addItem(i1, 5);

	// Customer c2(c1);
	// Customer c3;
	// c3 = c2;

	// if( c3 == c1 )
	// 	cout << "equal\n";

	// cout << c1;

	cout << "END\n";
	// cout<<o1;

	// Item array: [ID][count]
	// Customer c1, c2;

	// int item_arr1[4];
	// item_arr1[0] = 101;
	// item_arr1[1] = 5;
	// item_arr1[2] = 102;
	// item_arr1[3] = 19;

	// int item_arr2[4];
	// item_arr2[0] = 103;
	// item_arr2[1] = 21;
	// item_arr2[2] = 104;
	// item_arr2[3] = 37;

	// Order o1( &c1, item_arr1, 2 );
	// Order o2( &c2, item_arr2, 2 );
	// o1.print();
	// o2.print();

	// //o2 = o1;
	// //o2.print();

	// Order o3(o1);
	// o3.print();

	// cout << "Orders 1 and 2 are ";
	// if( o1 != o2 )
	// 	cout << "not ";
	// cout << "the same" << endl;

	// o3 = o3;

	// cout << o3;

	// o1.removeAllItems();
	// o2.removeAllItems();
	// o3.removeAllItems();

	// Order *o1 = new Order( &c1, item_arr, 2 );
	// o1->print();
	
	// Order *o2 = new Order( &c2, item_arr, 2 );
	// o2->print();

	// delete o1;
	// delete o2;
	
	exit(0);
}