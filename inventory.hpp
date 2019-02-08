/********************************************************
** Program: inventory.hpp
** Description: Header file for inventory class.
********************************************************/
#include <string>

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

class inventory
{
	private:  
    	vector<string> bag;

	public:
        inventory();
        vector<string> getInventory();
        void addToInventory(string);

};

#endif