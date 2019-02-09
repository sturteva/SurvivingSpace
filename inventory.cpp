/********************************************************
** Program: inventory.cpp
** Description: Implemenation file for player inventory
********************************************************/
#include "inventory.hpp"
#include "player.hpp"
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

/********************************************************
 ** Function: inventory()
 ** Description: constructor
 ** Parameters: None
*********************************************************/
inventory::inventory()
{

}

/********************************************************
 ** Function: getInventory()
 ** Description: Returns the players inventory
 ** Parameters: None
 ** Returns: Vector of sting containing player inventory
*********************************************************/
vector<string> inventory::getInventory()
{
	return bag;
}


/********************************************************
 ** Function: addToInventory()
 ** Description: Adds an item to the palyers inventory
 ** Parameters: String to be added to inventory
 ** Returns: None
*********************************************************/
void inventory::addToInventory(string item)
{
	bag.push_back(item);
}