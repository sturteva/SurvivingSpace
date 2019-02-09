/********************************************************
** Program: inventory.hpp
** Description: Header file for inventory class.
********************************************************/
#include <string>
#include <vector>

using std::string;
using std::vector;

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