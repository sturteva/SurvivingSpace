/*******************************************************************************
** Program: room.cpp
** Description: Implemenation file for room class.
*******************************************************************************/
#include "room.hpp"
#include <string>
#include <iostream>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::iterator; 

/*******************************************************************************
** Function: room ()
** Description: constructor
** Parameters: None
*******************************************************************************/
room::room()
{

    visited = false;
}

/*******************************************************************************
** Function: room ()
** Description: constructor when string passed
** Parameters: None
*******************************************************************************/
room::room(string n)
{
	name = n;
	visited = false;
}

/*******************************************************************************
 ** Function: setName()
 ** Description: sets the room name
 ** Parameters: string
 ** Returns: None
*******************************************************************************/
 void room::setName(string newName)
 {
    name = newName;
 }

/*******************************************************************************
** Function: getName()
** Description: gets the room name
** Parameters: None
** Returns: room name
*******************************************************************************/
string room::getName()
{
    return name;
}

/*******************************************************************************
** Function: setFD()
** Description: sets the long description name
** Parameters: string
** Returns: None
*******************************************************************************/
void room::setFD(string newFD)
{

    fullDesc = newFD;

}

/*******************************************************************************
** Function: setSD()
** Description: sets the short description name
** Parameters: string
** Returns: None
*******************************************************************************/
void room::setSD(string newSD)
{

    shortDesc = newSD;

}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the short description name
** Parameters: string
** Returns: None
*******************************************************************************/
void room::addInteractable(string newI)
{

    interactables.push_back(newI);
}

/*******************************************************************************
** Function: removeInteractable()
** Description: removes the item from the room object
** Parameters: Interactable item to be removed 
** Returns: None
*******************************************************************************/
void room::removeInteractable(string item)
{
    vector<string>::iterator i = find(interactables.begin(), interactables.end(), item);
    
    // Found the item
    interactables.erase(i);
    
}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the short description name
** Parameters: string
** Returns: None
*******************************************************************************/
void room::addAdjacent(room* newAdj)
{

    adjacent.push_back(newAdj);
}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the full description name
** Parameters: string
** Returns: full room description
*******************************************************************************/
//mostly used to save Gamestate
string room::getFullDesc()
{
    return fullDesc;
}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the short description name
** Parameters: string
** Returns: short room description
*******************************************************************************/
string room::getShortDesc()
{
    return shortDesc;
}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the short description name
** Parameters: string
** Returns: Vector of interactables in room
*******************************************************************************/
vector<string> room::getInteractables()
{

    return interactables;
}

/*******************************************************************************
** Function: addInteractable()
** Description: sets the short description name
** Parameters: string
** Returns: Vector of adjacent rooms
*******************************************************************************/
vector<room*> room::getAdjacent()
{

    return adjacent;
}

/*******************************************************************************
** Function: printDescription()
** Description: prints the room description
** Parameters: None
** Returns: None
*******************************************************************************/
 void room::printDescription()
 {
 	if(visited == false)
	{
		cout << getFullDesc() << endl;
		//visited = true;
	}
	else
	{
		cout << getShortDesc() << endl;
	}
 }

/*******************************************************************************
** Function: printRoomInfo()
** Description: prints room info. Used for debugging purposes. 
** Parameters: None
** Returns: None
*******************************************************************************/
 void room::printRoomInfo()
 {
    //name
    cout << "Room Name: " << name << endl;

    // Long Desc
    cout << "Full Desc: " << fullDesc << endl;
    
    // short desc
    cout << "Short Desc: " << shortDesc << endl;

    // interactables
    cout << "********** Interactables **********" << endl;
    for (int i = 0; i < (int)interactables.size(); i++)
    {
        cout << interactables[i] << endl;
    }
    // adjacent
    cout << "********** Adjacent **********" << endl;
    for (int i = 0; i < (int)adjacent.size(); i++)
    {
        cout << adjacent[i]->getName() << endl;
    }

    
 }


/*******************************************************************************
** Function: visitRoom()
** Description: changes the bool indicating the room has been visited
** Parameters: None
** Returns: None
*******************************************************************************/
void room::visitRoom()
{
    visited = true;
}