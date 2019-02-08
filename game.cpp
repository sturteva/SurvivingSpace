/*******************************************************************************
** Program: game.cpp
** Description: Implemenation file for game class.
*******************************************************************************/
using namespace std;
#include "game.hpp"
#include "room.hpp"
#include "player.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>


/*******************************************************************************
 ** Function: game ()
 ** Description: constructor
 ** Parameters: None
*******************************************************************************/
game::game()
{
	player1 = new player();
	numPlayers = 1;

}


/*******************************************************************************
 ** Function: initialize ()
 ** Description: initialize the rooms in gamestate
 ** Parameters: None
*******************************************************************************/
void game::initializeRooms()
{
    const char* directory = "./RoomFiles";
	//initialize rooms with files
	rooms = ourData.roomIO(directory);

	//Find starting room (not guaranteed to be first room in room vector
	room* firstRoom;

	for(int i = 0; i < (int)rooms.size(); ++i){
        if(rooms.at(i)->getName().compare("Starting Room") == 0){
            firstRoom = rooms.at(i);
            break;
        }
    }
	player1->setLocation(firstRoom);
}

 /******************************************************************************
 ** Function: start()
 ** Description: Starts the game loop
 ** Parameters: None
*******************************************************************************/
void game::start()
{
    //GameStatus status;
    string command;
    room * currRoom;

	do
	{
		currRoom = player1->getLocation();
		currRoom->printDescription();

		// ask for player input
		cout << "What would you like to do? (Type \"exit\" to stop adventure) ";
		cin >> command;
		cout << endl;

		// Check command contains no symbols
		while (checkAlpha(command) == false)
		{
			cout << "Only alpha numeric characters are allowed..." << endl; 
			cout << "What would you like to do? (Type \"exit\" to stop adventure) ";
			cin >> command;
			cout << endl;
		}

		// Parse command 


	}while (command != "exit");


}

 /******************************************************************************
 ** Function: getRooms()
 ** Description: returns room vector
 ** Parameters: None
*******************************************************************************/
vector<room*> game::getRooms()
{

    return rooms;
}

 /******************************************************************************
 ** Function: getRooms()
 ** Description: returns room vector
 ** Parameters: None
*******************************************************************************/
player* game::getPlayer1()
{
    return player1;
}

 /******************************************************************************
 ** Function: getRooms()
 ** Description: returns room vector
 ** Parameters: None
*******************************************************************************/
int game::getNumPlayers()
{

    return numPlayers;
}

 /******************************************************************************
 ** Function: setRooms()
 ** Description: sets new room vector
 ** Parameters: vector of rooms
*******************************************************************************/
void game::setRooms(vector<room*> newRooms)
{

    rooms = newRooms;
}
