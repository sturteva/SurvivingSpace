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
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::find;

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
		cout << "\nParsed Command: ";
		for (int count = 0; count < (int)command.size(); count++)
		{
			cout << command[count] << " ";
		}
		cout << endl << endl;

		// do command
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
	vector<string> roomItems;
	vector<string> currInventory;

	// get current room information
	currRoom = player1->getLocation();
	adjacentRooms = player1->getAdjacentRooms();
	roomItems = player1->getRoomItems();

	// get current inventory
	currInventory = player1->getInventory();



	// help command
	if (command[0] == "help")
	{
		//get room info
		currRoom->printRoomInfo();
		cout << endl;

		if (currRoom->getName() == "Starting Room")
		{
			cout << "'climb treetop' will take you to the Top of Tree" << endl
				 << "'look' will describe the items that can be interacted with" << endl
				 << "'take knfe' attempt to put knife in player inventory" << endl;
		}
		else if (currRoom->getName() == "Top of Tree")
		{
			cout << "'climb treebase' will take back down the base of the tree" << endl
				 << "'look' will describe the items that can be interacted with" << endl
				 << "'take bag' puts bag in player inventory" << endl;
		}


	}


	// go command
	if (command[0] == "go")
	{	
		//debug
		//cout << "Adjacent rooms: " << endl;

		
		for (int i = 0; i < (int)adjacentRooms.size(); i++)
		{
			//adjacentRooms[i]->printRoomInfo();
			
			if (adjacentRooms[i]->getName() == command[1])
			{
				cout << "Going to new location" << endl << endl;

				currRoom->visitRoom();
				player1->setLocation(adjacentRooms[i]);

				// get new room
				currRoom = player1->getLocation();
				currRoom->printDescription();
				break;
			}
			//cout << endl;
		}
	}

	// look command
	if (command[0] == "look")
	{
		if (currRoom->getName() == "Starting Room")
		{
			cout << "The bushes blocking the animal path are large and filled with thistles. I wonder whats on the other side?" << endl;
			//knife in room
			if (roomItems[0] == "Knife with Runes")
			{
				cout << "There is a large knife with strange runes all over it lying on the ground." << endl;

			}
		}

		// Top of Tree
		if (currRoom->getName() == "Top of Tree" && roomItems[0] == "Bag with Strange Runes")
		{
			cout << "To the west, you see some large grazing animals in a field, with some buildings in the distance." << endl
				 << "To the east, you see a small lake with fish in it." << endl;
			if (roomItems[0] == "Bag with Strange Runes")
			{
			cout << "There is a strange bag with runes sewn on it hanging from one of the tree branches." << endl
				 << "The runes look just like the ones on the knife down below." << endl; 
			}
		}
	}

	if (command [0] == "inventory")
		{
			if (currInventory.empty())
			{
				cout << "Player inventory is empty" << endl;
			}
			else
			{
				cout << "Player inventory: " << endl;

				for (int i = 0; i < (int)currInventory.size(); i++)
				{
					cout << currInventory[i] << endl;
				}
			}
		}

	// take command
	if (command[0] == "take")
	{
		// take knife
		if (currRoom->getName() == "Starting Room" && command[1] == "knife")
		{
			if(!currInventory.empty())  
			{
    			/* The bag is in inventory */
    			cout << "adding knife to inventory..." << endl;
    			player1->addToInventory("Knife with Runes");
    			currRoom->removeInteractable("Knife with Runes");
			} 
			else 
			{
    			/* player hasnt gotten the bag yet*/
    			cout << "The knife phases right through your hand. It appears you cannot pick it up." << endl;
			}
		}

		// take bag
		if (currRoom->getName() == "Top of Tree" && command[1] == "bag")
		{
			cout << "adding bag to inventory..." << endl;
			player1->addToInventory("Bag with Strange Runes");
    		currRoom->removeInteractable("Bag with Strange Runes");
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

