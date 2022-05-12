#include <iostream>

class Item {
	private:
		int ID;
		int ID_generator;
		float price;
		int expiration_date;

	public:
		Item();
		//~Item();
		int getID();
		float getPrice();
		int getExiprationDate();

}
