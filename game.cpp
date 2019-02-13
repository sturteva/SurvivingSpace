/*******************************************************************************
** Program: game.cpp
** Description: Implemenation file for game class.
*******************************************************************************/
#include "game.hpp"
#include "room.hpp"
#include "player.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

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
** Function: initializeRooms()
** Description: initializes the rooms in gamestate. Loads them from roomdat 
**              files.
** Parameters: None
** Returns: None
*******************************************************************************/
void game::initializeRooms()
{
    string directory = "./RoomFiles";
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

/*******************************************************************************
** Function: initializeDict ()
** Description: initializes the dictionary for parser
** Parameters: None
** Returns: None
*******************************************************************************/
void game::initializeDict()
{
	dictMapInit();
	//cout << "Initilizing parser dictionary..." << endl;
}


/******************************************************************************
** Function: start()
** Description: Starts the game loop
** Parameters: None
** Returns: None
*******************************************************************************/
void game::start()
{
    //GameStatus status;
	vector<string> command;
    //string input;
    room * currRoom;
	
	do
	{	
		// get current player location
		currRoom = player1->getLocation();
		currRoom->printDescription();

		// DEBUG
		//currRoom->printRoomInfo();

		/*
		// ask for player input
		cout << ">> ";
		cin >> input;
		cout << endl;

		// Check user input contains no symbols
		while (checkAlpha(input) == false)
		{
			cout << endl; 
			cout << ">> ";
			cin >> input;
			cout << endl;
		}
		*/

		// ask for player input and parse command
		command = parseString();
		
		//DEBUG
		cout << "Parsed Command: ";
		for (int count = 0; count < command.size(); count++)
		{
			cout << command[count] << " ";
		}
		cout << endl;

		// do command
		// only go is immplemented right now
		doCommand(command);

		cout << endl;

	}while (command[0] != "exit");
}

/******************************************************************************
** Function: doCommand()
** Description: carries out user command
** Parameters: Parsed command
** Returns: None
*******************************************************************************/
void game::doCommand(vector<string> command)
{
	// go command
	if (command[0] == "go")
	{
		vector<room*> adjacent;
		adjacent = player1->getAdjacentRooms();
		
		//debug
		cout << "Adjacent rooms: " << endl;
		
		for (int i = 0; i < adjacent.size(); i++)
		{
			cout << adjacent[i]->getName() << " ";
			if (adjacent[i]->getName() == command[1])
			{
				//cout << "Going to new location" << endl;
				player1->setLocation(adjacent[i]);
			}
			cout << endl;
		}
	}
}

/******************************************************************************
** Function: getRooms()
** Description: returns room vector
** Parameters: None
** Returns: Vector of rooms
*******************************************************************************/
vector<room*> game::getRooms()
{

    return rooms;
}

 /******************************************************************************
 ** Function: getRooms()
 ** Description: returns room vector
 ** Parameters: None
 ** Returns: pointer player object
*******************************************************************************/
player* game::getPlayer1()
{
    return player1;
}

 /******************************************************************************
 ** Function: getRooms()
 ** Description: returns room vector
 ** Parameters: None
 ** Returns: Int of number of players
*******************************************************************************/
int game::getNumPlayers()
{

    return numPlayers;
}

 /******************************************************************************
 ** Function: setRooms()
 ** Description: sets new room vector
 ** Parameters: vector of rooms
 ** Returns: None
*******************************************************************************/
void game::setRooms(vector<room*> newRooms)
{

    rooms = newRooms;
}
