/********************************************************
** Program: room.cpp
** Description: Implemenation file for room class.
********************************************************/
using namespace std;
#include "room.hpp"
#include <string>
#include <iostream>

room::room(){

    visited = false;
}

/********************************************************
 ** Function: room ()
 ** Description: constructor
 ** Parameters: None
 ********************************************************/
room::room(string n)
{
	name = n;
}

/********************************************************
 ** Function: setName()
 ** Description: sets the room name
 ** Parameters: string
 ********************************************************/
 void room::setName(string newName){
    name = newName;
 }

/********************************************************
 ** Function: getName()
 ** Description: gets the room name
 ** Parameters: None
 ********************************************************/
string room::getName()
{
    return name;
}
/********************************************************
 ** Function: printDescription()
 ** Description: prints the room description
 ** Parameters: None
 ********************************************************/
 void room::printDescription()
 {
 	if(visited == false)
	{
		cout << "This room looks new!" << endl;
		cout << "Name of room: " << name << endl;
		visited = true;
	}
	else
	{
		cout << "I've been here before! This is the " << name << endl;
		//cout << "The next room is the " << next->name << endl;
	}
 }
