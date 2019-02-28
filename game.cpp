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
		// ask for player input and parse command
		command = parseString();
		
		//DEBUG
		
		/*cout << "\nParsed Command: ";
		for (int count = 0; count < (int)command.size(); count++)
		{
			cout << command[count] << " ";
		}
		cout << endl << endl;
		*/

		cout << endl;

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
	// help command
	if (command[0] == "help")
	{
		helpCommand(command);
	}
	// go command
	else if (command[0] == "go")
	{	
		goCommand(command);
	}	
	// look command
	else if (command[0] == "look")
	{
		lookCommand(command);
	}
	// inventory command
	else if (command [0] == "inventory")
	{
		inventoryCommand(command);
	}
	// take command
	else if (command[0] == "take")
	{
		takeCommand(command);
	}
	// cut command
	else if (command[0] == "cut")
	{
		cutCommand(command);
	}

}

/******************************************************************************
** Function: helpCommand()
** Description: processes the help command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::helpCommand(vector<string> command)
{
	room * currRoom;
	currRoom = player1->getLocation();

	//get room info
	//currRoom->printRoomInfo();
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
	else if (currRoom->getName() == "Field with Grazing Animals")
	{
		cout << "help for 'Field with Grazing Animals'..." << endl;
	}
	else if (currRoom->getName() == "Pool of Water")
	{
		cout << "help for 'Pool of Water'..." << endl;
	}
}

/******************************************************************************
** Function: goCommand()
** Description: processes the go command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::goCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<room*> adjacentRooms = player1->getAdjacentRooms();
	vector<string> roomItems = player1->getRoomItems();

/*
	// get current room information
	currRoom = player1->getLocation();
	adjacentRooms = player1->getAdjacentRooms();
	roomItems = player1->getRoomItems();

	// get current inventory
	currInventory = player1->getInventory();
*/

	//debug
	//cout << "Adjacent rooms: " << endl;

	for (int i = 0; i < (int)adjacentRooms.size(); i++)
	{
		if (adjacentRooms[i]->getName() == command[1])
		{
			// starting room movement
			if (currRoom->getName() == "Starting Room")
			{
				if (command[1] == "Pool of Water" || command[1] == "Field with Grazing Animals")
				{
					if (find(roomItems.begin(), roomItems.end(), "Pile of Bushes") != roomItems.end() || roomItems.empty())
					{
						cout << "Going to new location" << endl << endl;
						currRoom->visitRoom();
						player1->setLocation(adjacentRooms[i]);

						// get new room
						currRoom = player1->getLocation();
						currRoom->printDescription();
					}
					else
					{
						cout << "Those thistles will tear me up. Maybe I could use the knife to chop down the bushes..." << endl;
					}
				}
				else
				{
					cout << "Going to new location" << endl << endl;
					currRoom->visitRoom();
					player1->setLocation(adjacentRooms[i]);

					// get new room
					currRoom = player1->getLocation();
					currRoom->printDescription();
				}
			}

			/*
			if (adjacentRooms[i]->getName() == "Pool of Water" || adjacentRooms[i]->getName() == "Field with Grazing Animals")
			{
				if (find(currInventory.begin(), currInventory.end(), "Knife with Runes") != currInventory.end() )
				{
					cout << "You use the knife to chop down the bushes..." << endl << endl;
					currRoom->visitRoom();
					player1->setLocation(adjacentRooms[i]);

					// get new room
					currRoom = player1->getLocation();
					currRoom->printDescription();
				}
				else
				{
						cout << "Those thistles will tear me up.. I bet that knife could chop down the bushes..." << endl;
				}
			}*/

			// all other rooms
			else
			{
				cout << "Going to new location" << endl << endl;

				currRoom->visitRoom();
				player1->setLocation(adjacentRooms[i]);

				// get new room
				currRoom = player1->getLocation();
				currRoom->printDescription();
			}
		}
	}
}

/******************************************************************************
** Function: lookCommand()
** Description: processes the look command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::lookCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> roomItems = player1->getRoomItems();

	// Starting Room
	if (currRoom->getName() == "Starting Room")
	{
		cout << "The bushes blocking the animal path are large and filled with thistles. I wonder whats on the other side?" << endl;
		//knife in room
		if (find(roomItems.begin(), roomItems.end(), "Knife with Runes") != roomItems.end())
		{
			cout << "There is a large knife with strange runes all over it lying on the ground." << endl;
		}
	}

	// Top of Tree
	if (currRoom->getName() == "Top of Tree")
	{
		cout << "To the west, you see some large grazing animals in a field, with some buildings in the distance." << endl
			 << "To the east, you see a small lake with fish in it." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Bag with Strange Runes") != roomItems.end())
		{
			cout << "There is a strange bag with runes sewn on it hanging from one of the tree branches." << endl
			 	 << "The runes look just like the ones on the knife down below." << endl; 
		}
	}

	// Field with Grazing Animals
	if (currRoom->getName() == "Field with Grazing Animals" )
	{
		if (find(roomItems.begin(), roomItems.end(), "Grazing Animal with a strange rock on its back") != roomItems.end())
		{
			cout << "You notice one of the grazing animals has a rock with strange symbols on its back." << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "Red Ochre rock") != roomItems.end())
		{
			cout << "There is a pile of soft red rocks you identify as red ochre." << endl; 
		}	
	}
	// Pool of Water
	if (currRoom->getName() == "Pool of Water")
	{
		cout << "A trail runs to the south toward what looks like a cave carved into one of the hills." << endl
			 << "Another trail runs to the east that leads ot a rock outcropping overlooking the water.." << endl
			 << "You can see through the crystal clear water and see the fish swimming." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Fish") != roomItems.end())
		{
			cout << "There are a lot of fish swimming in the water. Maybe I could find something to fish one out" << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "Water") != roomItems.end())
		{
			cout << "The water looks crystal clear." << endl; 
		}
	}
}

/******************************************************************************
** Function: inventoryCommand()
** Description: processes the inventory command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::inventoryCommand(vector<string> command)
{
	vector<string> currInventory = player1->getInventory();

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

/******************************************************************************
** Function: takeCommand()
** Description: processes the take command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::takeCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	// take knife
	if (currRoom->getName() == "Starting Room" && command[1] == "knife")
	{
		if(!currInventory.empty())  
		{
			/* The bag is in inventory */
			cout << "You put the knife in the bag, but the small bag does not grow... \nThe bag appears to be enchanted to hold items without growing." << endl;
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
		cout << "You take the bag and clip it to your belt..." << endl;
		player1->addToInventory("Bag with Strange Runes");
		currRoom->removeInteractable("Bag with Strange Runes");
	}
}

/******************************************************************************
** Function: cutCommand()
** Description: processes the cut command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::cutCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	//cout << "cut command sent..." << endl;
	// cut bushes
	if (command[1] == "bushes")
	{
		//check knife is in inventory
		if (find(currInventory.begin(), currInventory.end(), "Knife with Runes") != currInventory.end() )
		{
			cout << "You cut the bushes using the knife with the strange runes to reveal the field to the west and the small lake to the east. \nOnly a large branch remains on the ground next to you." << endl;
			//remove bushes from interactables
			currRoom->removeInteractable("Thistle filled bushes");
			// add pile of bushes to interactables
			currRoom->addInteractable("Large Branch");
		}
		else
		{
			cout << "Those thistles will tear me up.. I need a knife to chop down those bushes..." << endl;
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

