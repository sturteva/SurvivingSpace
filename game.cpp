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
    //room * currRoom;
	
	do
	{	
		// get current player location
		//currRoom = player1->getLocation();
		//currRoom->printDescription();

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
		for (int count = 0; count < (int)command.size(); count++)
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
	room * currRoom;
	vector<room*> adjacentRooms;
	vector<string> items;

	// get current room information
	currRoom = player1->getLocation();
	adjacentRooms = player1->getAdjacentRooms();
	items = player1->getRoomItems();


	// help command
	if (command[0] == "help")
	{
		if (currRoom->getName() == "Starting Room")
		{
			cout << "'climb tree' will take you to the Top of Tree" << endl
				 << "'look' will describe the items that can be interacted with" << endl
				 << "'take knfe' attempt to put knife in player inventory" << endl;
		}


	}


	// go command
	if (command[0] == "go")
	{	
		//debug
		//cout << "Adjacent rooms: " << endl;
		
		for (int i = 0; i < (int)adjacentRooms.size(); i++)
		{
			//cout << adjacent[i]->getName() << " ";
			if (adjacentRooms[i]->getName() == command[1])
			{
				cout << "Going to new location" << endl;
				player1->setLocation(adjacentRooms[i]);
				break;
			}
			//cout << endl;
		}
	}

	// look command
	if (command[0] == "look")
	{
		if (currRoom->getName() == "Starting Room" && items[0] == "Knife with Runes")
		{
			cout << "There is a large knife with strange runes all over it lying on the ground." << endl;
		}
		if (currRoom->getName() == "Starting Room")
		{
			cout << "The bushes blocking the animal path are large and filled with thistles. I wonder whats on the other side?" << endl;
		}
		if (currRoom->getName() == "Top of Tree" && items[0] == "Bag with Strange Runes")
		{
			"There is a strange bag with runes sewn on it hanging from one of the tree branches." << endl;
		}
	}

	// take command
	if (command[0] == "take")
	{
		if (currRoom->getName() == "Starting Room" && command[1] == "knife")
		{
			cout << "take knife from Starting Room" << endl;
			if (player1->)
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
