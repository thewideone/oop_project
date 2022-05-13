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
	Order o1;
	Customer c1,c2;
	o1.setCustomer(&c2);
	cout << "assigned " << c1.getID() << endl;
	
	o1.addItem( i1, 5 );

	Order o2;
	o2 = o1;

	cout << o1;

	if( o2 == o1 )
		cout << "equal\n";

	OrderList l1;
	l1.addElement(o1);
	l1.addElement(o2);
	OrderList l2;
	l2 = l1;
	cout << l2;

	Shop s1("ALABAMA");
	s1.addItem(i1, 10);
	s1.addItem(i2, 102);
	cout << s1;

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