#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>

#include "debug.hpp"

using namespace std;

class Item {
	private:
		int ID;
		static int ID_generator;
		float price;
		int expiration_date;

	public:
		Item( float price, int exp_date );
		Item( const Item& other );
		// ~Item();
		int getID() const;
		float getPrice() const;
		int getExiprationDate() const;
		bool setPrice( float new_price );		// returns true if operation succeeded
		bool setExiprationDate( int new_date );	// returns true if operation succeeded

		Item& operator=( const Item& other );
		bool operator==( const Item& other ) const;
		bool operator!=( const Item& other ) const;

		friend ostream& operator<<( ostream& out, const Item& item );
};

#endif /* _ITEM_HPP_ */