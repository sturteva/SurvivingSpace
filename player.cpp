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

vector<room*> player::getAdjacentRooms()
{
	return location->getAdjacent();
}