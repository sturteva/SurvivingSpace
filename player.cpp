/********************************************************
** Program: player.cpp
** Description: Implemenation file for player class.
********************************************************/
#include "player.hpp"
#include "room.hpp"
#include <string>
#include <iostream>

using std::vector;

/*********************************************************
** Function: player()
** Description: constructor
** Parameters: None
*********************************************************/
player::player()
{

}

/********************************************************
 ** Function: getLocation()
 ** Description: returns the room location of the player
 ** Parameters: None
 ** Returns: Pointer to room player is currently in.
 ********************************************************/
room* player::getLocation()
{
    return location;
}

/********************************************************
 ** Function: setLocation ()
 ** Description: sets the player location
 ** Parameters: Room address
 ** Returns: None
 ********************************************************/
void player::setLocation(room *r)
{
    location = r;
}

/********************************************************
 ** Function: getAdjacentRooms()
 ** Description: gets adjacent rooms to current room
 ** Parameters: None
 ** Returns: Vector of adjacent rooms
 ********************************************************/
vector<room*> player::getAdjacentRooms()
{
	return location->getAdjacent();
}

/********************************************************
 ** Function: getRoomItems()
 ** Description: gets adjacent rooms to current room
 ** Parameters: None
 ** Returns: Vector of adjacent rooms
 ********************************************************/
vector<string> player::getRoomItems()
{
	return location->getInteractables();
}

/********************************************************
 ** Function: addInventory()
 ** Description: adds item to player inventory
 ** Parameters: Item to be added
 ** Returns: None
 ********************************************************/
void player::addToInventory(string item)
{
	playerInventory.push_back(item);
}

/********************************************************
 ** Function: getInvnetory()
 ** Description: gets player inventory
 ** Parameters: None
 ** Returns: player inventory
 ********************************************************/
vector<string> player::getInventory()
{
	return playerInventory; 
}