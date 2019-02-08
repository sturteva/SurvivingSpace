/********************************************************
** Program: inventory.cpp
** Description: Implemenation file for player inventory
********************************************************/
using namespace std;

#include "inventory.hpp"
#include "player.hpp"
#include <string>
#include <iostream>
#include <vector>


/********************************************************
 ** Function: inventory()
 ** Description: constructor
 ** Parameters: None
*********************************************************/
inventory::inventory()
{

}

/********************************************************
 ** Function: 
 ** Description: 
 ** Parameters: 
*********************************************************/
vector<string> inventory::getInventory()
{
	return bag;
}



void inventory::addToInventory(string item)
{
	bag.push_back(item);
}