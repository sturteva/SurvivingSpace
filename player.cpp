/********************************************************
** Program: player.cpp
** Description: Implemenation file for player class.
********************************************************/
using namespace std;
#include "player.hpp"
#include "room.hpp"
#include <string>
#include <iostream>


/********************************************************
 ** Function: player()
 ** Description: constructor
 ** Parameters: None
 ********************************************************/
player::player()
{

}

/********************************************************
 ** Function: getLocation ()
 ** Description: returns the room location of the player
 ** Parameters: None
 ********************************************************/
room* player::getLocation()
{
    return location;
}

/********************************************************
 ** Function: setLocation ()
 ** Description: sets the player location
 ** Parameters: Room address
 ********************************************************/
void player::setLocation(room *r)
{
    location = r;
}