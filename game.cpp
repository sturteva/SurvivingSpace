/*******************************************************************************
** Program: game.cpp
** Description: Implemenation file for game class.
*******************************************************************************/
#include "game.hpp"
#include "room.hpp"
#include "player.hpp"
#include "parser.hpp"
#include "dataio.hpp"
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
		/*
		cout << "\nParsed Command: ";
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
	// save command
	else if (command[0] == "savegame")
	{	
		saveCommand(command);
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
	// look at command
	else if (command[0] == "look at")
	{
		lookAtCommand(command);
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
	else if (command[0] == "move toward")
	{
		moveTowardCommand(command);
	}
	else if (command[0] == "sneak")
	{
		sneakCommand(command);
	}
	else if (command[0] == "exit")
	{

	}
	else
	{
		cout << "That command is not recognized... Please try again." << endl;
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
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'take knfe' attempt to put knife in player inventory" << endl
			 << "'go pool of water' will go to thr large pool of water once thistle bushes have been cut" << endl
			 << "'go field' will go to the field with grazing animals once thistle bushes have been cut" << endl;
	}
	else if (currRoom->getName() == "Top of Tree")
	{
		cout << "'climb treebase' will take back down the base of the tree" << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'take bag' puts bag in player inventory" << endl;
	}
	else if (currRoom->getName() == "Field with Grazing Animals")
	{
		cout << "'go ruins' will take you to the ruins in the distance" << endl
			 << "'go cave' will take you to the cave further down the trail" << endl
			 << "'go start' will take you back to the tree you woke up under." << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'sneak up on grazing animal' will sneak up behind the animal to examine the strange rock"
			 << "'take red rock' will take the Red Ochre rock found on the ground" << endl;
	}
	else if (currRoom->getName() == "Pool of Water")
	{
		cout << "'go rock outcropping' will take you to the rock outcropping overlooking the water " << endl
			 << "'go cave' will take you to the cave in the distance" << endl
			 << "'go start' will take you back to the tree you woke up under." << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'move toward grazing animal' will move you closer to the grazing animals"
			 << "'sneak up on grazing animal' will sneak up behind the animal to examine the strange rock" << endl
			 << "'take rock' will take the Red Ochre rock found on the ground" << endl;
	}
	else if (currRoom->getName() == "Predator Den")
	{
		cout << "'go pool of water' will take you to the large pool of water" << endl
			 << "'go cave' will take you to the cave in the distance" << endl
			 << "'go start' will take you back to the tree you woke up under" << endl;
	}
	else if (currRoom->getName() == "Tech Ruin")
	{
		cout << "'go field' will go to the field with grazing animals" << endl
			 << "'take rock with lightning symbol' will take the rock with strange symbol found in the rubble" << endl
			 << "'take hook' will take the aluminium hook found in the rubble" << endl
			 << "'look at old datapad' will examine the old datapad found in the street" << endl;
	}
	else if (currRoom->getName() == "Caves")
	{
		cout << "'go field' will go to the field with grazing animals" << endl
			 << "'go pool of water' will take you to the large pool of water" << endl
			 << "'go predator den' will take you to the predator den overlooking the water " << endl
			 << "'go field' will go to the field with grazing animals" << endl
			 << "'take string like vines' will take some of the vines covering the cave entrance." << endl;
	}
	else if (currRoom->getName() == "Magic Dome")
	{
		cout << "'go field' will go to the field with grazing animals" << endl
			 << "'place <item> in <slot>' will place item from inventory in the specified altar slot" << endl;
	}
}

/******************************************************************************
** Function: saveCommand()
** Description: processes the help command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::saveCommand(vector<string> command)
{
	cout << "saving game state..." << endl;
	ourData.saveGame(*this);
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
					if (find(roomItems.begin(), roomItems.end(), "Pile of cut bushes") != roomItems.end() || roomItems.empty())
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
				else if(command[1] == "Top of Tree")
				{
					cout << "Going to new location" << endl << endl;
					currRoom->visitRoom();
					player1->setLocation(adjacentRooms[i]);

					// get new room
					currRoom = player1->getLocation();
					currRoom->printDescription();
					break;
				}
			}
			// move away from animal
			/*else if(currRoom->getName() == "Field with Grazing Animals")
			{
				if(find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
				{
					currRoom->removeInteractable("Sneak up on Animal");
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
	else if (currRoom->getName() == "Top of Tree")
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
	else if (currRoom->getName() == "Field with Grazing Animals" )
	{
		cout << "In the distance you can see what looks like buildings." << endl
			 << "In the forest to the west you see a cave entrance." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Grazing Animal with a strange rock on its back") != roomItems.end())
		{
			cout << "You notice one of the grazing animals has a rock with strange symbols on its back." << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "Red Ochre rock") != roomItems.end())
		{
			cout << "There is a pile of soft red rocks on the ground." << endl;
		}	
	}

	// Pool of Water
	else if (currRoom->getName() == "Pool of Water")
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

	// predator den
	else if (currRoom->getName() == "Predator Den")
	{
		if (find(roomItems.begin(), roomItems.end(), "Rock with Spiral Symbol") != roomItems.end())
		{
			cout << "You see a small rock with a spiral symbol on it behind the predator." << endl
				 << "I wonder if I could distract him with something to grab the strange stone." << endl;
		}
	}

	// tech ruin
	else if (currRoom->getName() == "Tech Ruin")
	{
		cout << "What used to be large buildings long ago, appear half crumbling and falling apart." << endl
			 << "Some of these buildings appear to have once been a school, hospital, warehouse, and even some sort of civic center." << endl
			 << "The architecture is foreign to you, but some of the galaxy-wide accepted symbols are present." << endl
			 << "There is rubble and trash left from whoever built these buildings." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Aluminum Hook") != roomItems.end())
		{
			cout << "Among the rubble you see an aluminum hook similar to a fishing hook." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Rock with Lightning Symbol") != roomItems.end())
		{
			cout << "You also spot a small rock with a lightning symbol on it." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Old datapad") != roomItems.end())
		{
			cout << "There is an old datapad lying in the middle of the street." << endl;
		}

	}

	else if (currRoom->getName() == "Caves")
	{
		cout << "The entrance to the cave is covered by small string like vines." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Door with strange writing") != roomItems.end())
		{
			cout << "You see a door deeper within the cave with strange writing above it." << endl;
		}
	}

	else if (currRoom->getName() == "Magic Dome")
	{
		cout << "You see an altar with some strange writing on it. Tht altar has 3 slots on the top about the size of those strange rocks ive been seeing." << endl;
	}

}

/******************************************************************************
** Function: lookAtCommand()
** Description: processes the look at command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::lookAtCommand(vector<string> command)
{
	vector<string> roomItems = player1->getRoomItems();

	if (command[1] == "Knife with Runes")
	{ 
		cout << "It is a large knife, about 10 inches long. There are strange runes printed all over the blade." << endl;
	}
	else if (command[1] == "Thistle filled bushes")
	{
		cout << "The bushes are thick and you are unable to see through to the other side..." << endl
			 << "The thorns on the branches are long and look painful." << endl;
	}
	else if (command[1] == "Bag with Strange Runes")
	{
		cout << "It is a small bag with a clip that looks like its for your belt" << endl
			 << "There are runes printed all over the outside of the bag. They appear to match the ones seen on the knife below." << endl;
	}
	else if (command[1] == "Grazing Animal with a strange rock on its back")
	{
		if(find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "The rock is round, smooth and has a sword like symbol on it. I bet I could take it without the animal knowing." << endl;
		}
		else
		{
			cout << "The animal is large, violet colored and roughly the size of horses from the planet Terra in the system of Sol." << endl
				 << "You notice what looks like a small rock balanced on its back." << endl
				 << "If I was a little closer, maybe I could see what type of rock it is." << endl;
		}
	}
	else if (command[1] == "Red Ochre rock")
	{
		cout << "The red rocks on the ground look to be Red Ochre." << endl
			 << "They look soft and could probably be crushed into a powder." << endl;
	}
	else if (command[1] == "Aluminum Hook")
	{
		cout << "It is a small aluminum hook. It looks like it used to be used for fishing." << endl;
	}
		else if (command[1] == "Rock with Lightning Symbol")
	{
		cout << "It is a small smooth rock with a lighning symbol in the middle." << endl;
	}
		else if (command[1] == "Old datapad")
	{
		cout << "It is an old datapad that was once owned by an inhabitant of the abandonded city." << endl
			 << "There is a note pulled up on the screen that reads:" << endl
			 << "'This planet is fighting and protecting itself every step of the way, as we try to colonize this planet." << endl
			 << "Whatever it is, it always tries to just scare us first before it attacks with any seriousness. " << endl
			 << "We've decided to just abandon this colony and go back to Zelon." << endl
			 << "Strange, as soon as we started packing up, all of our problems stopped, almost as if the planet wanted to help us leave quickly'" << endl;
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
		cout << "You currently have nothing in your inventory." << endl
			 << "Perhaps a bag would help carry items..." << endl;
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
	vector<string> roomItems = player1->getRoomItems();

	// take knife
	if (currRoom->getName() == "Starting Room" && command[1] == "Knife with Runes")
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
	else if (currRoom->getName() == "Top of Tree" && command[1] == "Bag with Strange Runes")
	{
		cout << "You take the bag and clip it to your belt..." << endl;
		player1->addToInventory("Bag with Strange Runes");
		currRoom->removeInteractable("Bag with Strange Runes");
	}
	
	// take rock
	// field
	else if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "rock")
	{
		if (find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "You take the strange rock off the animals back and put it into your bag." << endl
				 << "The animal doesn't seem to be bothered. It just shakes and moves to a new patch of grass." << endl;

			currRoom->removeInteractable("Grazing Animal with a strange rock on its back");
			player1->addToInventory("Rock with Sword Symbol");
			currRoom->addInteractable("Grazing Animal");
		}
		else
		{
			cout << " You are too far away to reach the rock... Try moving closer." << endl;
		}
	}
	// tech ruin
	else if (currRoom->getName() == "Tech Ruin" && command[1] == "rock")
	{
		cout << "You pick up the rock with the lightning symbol and put it in your bag." << endl;
		player1->addToInventory("Rock with Lightning Symbol");
		currRoom->removeInteractable("Rock with Lightning Symbol");
	}
	// =========== TODO ============
	// predator den
	else if (currRoom->getName() == "Predator Den" && command[1] == "rock")
	{

	}

	// 'take rock off back'
	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Rock with Sword Symbol")
	{
		if (find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "You take the strange rock off the animals back and put it into your bag." << endl
				 << "The animal doesn't seem to be bothered. It just shakes and moves to a new patch of grass." << endl;

			currRoom->removeInteractable("Grazing Animal with a strange rock on its back");
			player1->addToInventory("Rock with Sword Symbol");
			currRoom->addInteractable("Grazing Animal");
		}
		else
		{
			cout << " You are too far away to reach the rock... Try moving closer." << endl;
		}
	}
	// 'take rock with lightning symbol'
	if (currRoom->getName() == "Tech Ruin" && command[1] == "Rock with Lightning Symbol")
	{
		cout << "You pick up the rock with the lightning symbol and put it in your bag." << endl;
		player1->addToInventory("Rock with Lightning Symbol");
		currRoom->removeInteractable("Rock with Lightning Symbol");
	}

	// 'take hook'
	if (currRoom->getName() == "Tech Ruin" && command[1] == "Aluminum Hook")
	{
		cout << "You pick up the aluminum hook and put it in your bag." << endl;
		player1->addToInventory("Aluminum Hook");
		currRoom->removeInteractable("Aluminum Hook");
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
	vector<string> roomItems = player1->getRoomItems();

	//cout << "cut command sent..." << endl;
	// cut bushes
	if (command[1] == "Thistle filled bushes")
	{
		//check knife is in inventory
		if (find(currInventory.begin(), currInventory.end(), "Knife with Runes") != currInventory.end() )
		{
			cout << "You cut the bushes using the knife with the strange runes to reveal the field to the west and the small lake to the east. \nOnly a pile of cut bushes remains." << endl;
			//remove bushes from interactables
			currRoom->removeInteractable("Thistle filled bushes");
			// add pile of bushes to interactables
			currRoom->addInteractable("Pile of cut bushes");
		}
		else
		{
			cout << "Those thistles will tear me up.. I need a knife to chop down those bushes..." << endl;
		}
	}

	// rock off animals back
	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Rock with Sword Symbol")
	{
		if (find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "You cut the strange rock off the animals back with your knife." << endl
				 << "The animal gets spooked and takes off running." << endl;
		}
		else
		{
			cout << " You are too far away to reach the rock... Try moving closer." << endl;
		}
	}
}


/******************************************************************************
** Function: moveTowardCommand()
** Description: processes the move toward command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::moveTowardCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();

	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Grazing Animal with a strange rock on its back")
	{
		cout << "The herd senses you and moves further along the plains, but you can still see them." << endl
			 << "Maybe I should be more stealthy next time..." << endl;
	} 

}

/******************************************************************************
** Function: sneakCommand()
** Description: processes the move toward command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::sneakCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();

	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Grazing Animal with a strange rock on its back")
	{
		cout << "You sneak up on the grazing animal with the strange rock on its back..." << endl
			 << "You notice the rock is round, smooth, and has a sword like symbol on it." << endl
			 << "If I'm careful I could probably grab the strange rock off the animals back." << endl;
		currRoom->addInteractable("Sneak up on Animal");
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

 /******************************************************************************
 ** Function: setRooms()
 ** Description: sets player 
 ** Parameters: point to a player
 ** Returns: None
 ******************************************************************************/
void game::setPlayers(player* p1){

	player1 = p1;
}


