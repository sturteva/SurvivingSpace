/********************************************************
** Program: inventory.hpp
** Description: Header file for inventory class.
********************************************************/
using namespace std;
#include <string>
#include <vector>

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