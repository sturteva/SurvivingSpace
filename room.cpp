/*******************************************************************************
** Program: room.cpp
** Description: Implemenation file for room class.
*******************************************************************************/
using namespace std;
#include "room.hpp"
#include <string>
#include <iostream>

room::room()
{

    visited = false;
}

/*******************************************************************************
 ** Function: room ()
 ** Description: constructor
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
*******************************************************************************/
 void room::setName(string newName)
 {
    name = newName;
 }

/*******************************************************************************
 ** Function: getName()
 ** Description: gets the room name
 ** Parameters: None
*******************************************************************************/
string room::getName()
{
    return name;
}

/*******************************************************************************
 ** Function: setFD()
 ** Description: sets the long description name
 ** Parameters: string
*******************************************************************************/
void room::setFD(string newFD)
{

    fullDesc = newFD;

}

/*******************************************************************************
 ** Function: setSD()
 ** Description: sets the short description name
 ** Parameters: string
*******************************************************************************/
void room::setSD(string newSD)
{

    shortDesc = newSD;

}

/*******************************************************************************
 ** Function: addInteractable()
 ** Description: sets the short description name
 ** Parameters: string
*******************************************************************************/
void room::addInteractable(string newI)
{

    interactables.push_back(newI);
}

/*******************************************************************************
 ** Function: addInteractable()
 ** Description: sets the short description name
 ** Parameters: string
*******************************************************************************/
void room::addAdjacent(room* newAdj)
{

    adjacent.push_back(newAdj);
}

/*******************************************************************************
 ** Function: addInteractable()
 ** Description: sets the full description name
 ** Parameters: string
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
*******************************************************************************/
string room::getShortDesc()
{
    return shortDesc;
}

/*******************************************************************************
 ** Function: addInteractable()
 ** Description: sets the short description name
 ** Parameters: string
*******************************************************************************/
vector<string> room::getInteractables()
{

    return interactables;
}

/*******************************************************************************
 ** Function: addInteractable()
 ** Description: sets the short description name
 ** Parameters: string
*******************************************************************************/
vector<room*> room::getAdjacent()
{

    return adjacent;
}

/*******************************************************************************
 ** Function: printDescription()
 ** Description: prints the room description
 ** Parameters: None
*******************************************************************************/
 void room::printDescription()
 {
 	if(visited == false)
	{
		cout << getFullDesc() << endl;
		visited = true;
	}
	else
	{
		cout << getShortDesc() << endl;
	}
 }
