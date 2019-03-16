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
#include <stdlib.h> 
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::find;

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/*******************************************************************************
** Function: game ()
** Description: constructor
** Parameters: None
*******************************************************************************/
game::game()
{
	player1 = new player();
	numPlayers = 1;
	predatorCounter = 0;
	sneakFlag = false;
	magicDomeOpen = false;
	rugvukFlag = false;
	engineFixed = false;

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

void game::loadGameFromFolder(string folder)
{
	ourData.loadGame(folder,this);
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
    currRoom = player1->getLocation();
    currRoom->printDescription();

	do
	{
		// ask for player input and parse command
		command = parseString();
		//DEBUG
		
/*		cout << "\nParsed Command: ";
		for (int count = 0; count < (int)command.size(); count++)
		{
			cout << command[count] << " ";
		}
		cout << endl << endl;*/
		

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
	// move toward command
	else if (command[0] == "move toward")
	{
		moveTowardCommand(command);
	}
	// sneak command
	else if (command[0] == "sneak")
	{
		sneakCommand(command);
	}
	// put command
	else if (command[0] == "put")
	{
		putCommand(command);
	}
	// drop command
	else if (command[0] == "drop")
	{
		dropCommand(command);
	}
	// crush command
	else if (command[0] == "crush")
	{
		crushCommand(command);
	}
	// combine command
	else if (command[0] == "combine")
	{
		combineCommand(command);
	}
	// give command
	else if (command[0] == "give")
	{
		giveCommand(command);
	}
	// use command
	else if (command[0] == "use")
	{
		useCommand(command);
	}
	// fix command
	else if (command[0] == "fix")
	{
		fixCommand(command);
	} 
	// exit command
	else if (command[0] == "exit")
	{

	}
	else
	{
		cout << "That command is not recognized... Please try again" << endl;
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
			 << "'go pool of water' will go to the large pool of water once thistle bushes have been cut" << endl
			 << "'go field' will go to the field with grazing animals once thistle bushes have been cut" << endl;
	}
	else if (currRoom->getName() == "Top of Tree")
	{
		cout << "'climb treebase' will take back down the base of the tree" << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'take bag' puts bag in player inventory" << endl
			 << "'take branch' puts large branch in player inventory" << endl;
	}
	else if (currRoom->getName() == "Field with Grazing Animals")
	{
		cout << "'go ruins' will take you to the ruins in the distance" << endl
			 << "'go cave' will take you to the cave further down the trail" << endl
			 << "'go treebase' will take you back to the tree you woke up under." << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'sneak up on grazing animal' will sneak up behind the animal to examine the strange stone"
			 << "'take stone' will try to take the strange stone off the grazing animal" << endl
			 << "'take red rock' will take the Red Ochre rock found on the ground" << endl;
	}
	else if (currRoom->getName() == "Pool of Water")
	{
		cout << "'go rock outcropping' will take you to the rock outcropping overlooking the water " << endl
			 << "'go predator den' will take you to the rock outcropping overlooking the water " << endl
			 << "'go cave' will take you to the cave in the distance" << endl
			 << "'go start' will take you back to the tree you woke up under." << endl
			 << "'look around' will describe the items that can be interacted with" << endl
			 << "'take water bottle' will take the water bottle found near the water" << endl;
	}
	else if (currRoom->getName() == "Predator Den")
	{
		cout << "'go pool of water' will take you to the large pool of water" << endl
			 << "'go cave' will take you to the cave in the distance" << endl
			 << "'go start' will take you back to the tree you woke up under" << endl
			 << "'take stone' will take the stone with strange symbol found in the rubble" << endl;
	}
	else if (currRoom->getName() == "Tech Ruin")
	{
		cout << "'go field' will go to the field with grazing animals" << endl
			 << "'take stone' will take the stone with strange symbol found in the rubble" << endl
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
	vector<room*> adjacentRooms = currRoom->getAdjacent();
	vector<string> adjacentDirs = currRoom->getAdjDir();
	vector<string> roomItems = player1->getRoomItems();

/*
	// get current room information
	currRoom = player1->getLocation();
	adjacentRooms = player1->getAdjacentRooms();
	roomItems = player1->getRoomItems();

	// get current inventory
	currInventory = player1->getInventory();
*/

	if(command[1] == "tree" && currRoom->getName() == "Starting Room")
	{
		cout << "Going to new location" << endl << endl;
		currRoom->visitRoom();
		for (int i = 0; i < (int)adjacentRooms.size(); i++)
		{
			if(adjacentRooms[i]->getName() == "Top of Tree")
			{
				player1->setLocation(adjacentRooms[i]);
				// get new room
				currRoom = player1->getLocation();
				currRoom->printDescription();
				break;
			}
		}
	}


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
						break;
					}
					else
					{
						cout << "Those thistles will tear me up. Maybe I could use the " << BOLDGREEN << "knife" << RESET << " to chop down the bushes..." << endl;
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
			else if(currRoom->getName() == "Caves")
			{
				if(magicDomeOpen && command[1] == "Magic Dome" )
				{
					cout << "Going to new location" << endl << endl;
					currRoom->visitRoom();
					player1->setLocation(adjacentRooms[i]);

					// get new room
					currRoom = player1->getLocation();
					currRoom->printDescription();
					break;
				}
				else if(command[1] == "Magic Dome")
				{
					cout << "The large stone door is shut tight..." << endl;
				}

				else{

					cout << "Going to new location" << endl << endl;
                                        currRoom->visitRoom();
                                        player1->setLocation(adjacentRooms[i]);

                                        // get new room
                                        currRoom = player1->getLocation();
                                        currRoom->printDescription();
                                        break;

				}
			}
			// all other rooms
			else
			{
				if (currRoom->getName() == "Field with Grazing Animals")
				{
					sneakFlag = false; 
				}
				cout << "Going to new location" << endl << endl;

				currRoom->visitRoom();
				player1->setLocation(adjacentRooms[i]);

				// get new room
				currRoom = player1->getLocation();
				currRoom->printDescription();
				break;
			}
		}
	}

	for (int i = 0; i < (int)adjacentDirs.size(); i++)
	{
		if (adjacentDirs[i] == command[1])
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
		cout << "To the" << BOLDYELLOW << " west" << RESET << ", you see some large " << BOLDYELLOW << "grazing animals in a field" << RESET << ", with some buildings in the distance." << endl
			 << "To the" << BOLDYELLOW << " east" << RESET << " , you see a small lake with fish in it." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Bag with Strange Runes") != roomItems.end())
		{
			cout << "There is a" << BOLDGREEN "  strange bag with runes" << RESET << " sewn on it hanging from one of the tree branches." << endl
			 	 << "The runes look just like the ones on the knife down below." << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "leafs filled branch") != roomItems.end())
		{
			cout << "There is a large tree" << BOLDGREEN " branch" << RESET << " that would make a great pole." << endl; 
		}
	}

	// Field with Grazing Animals
	else if (currRoom->getName() == "Field with Grazing Animals" )
	{
		cout << "In the distance you can see what looks like buildings." << endl
			 << "In the forest to the west you see a cave entrance." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Grazing Animal with a strange rock on its back") != roomItems.end())
		{
			cout << "You notice one of the grazing animals has a" << BOLDGREEN << " rock with strange symbols" << RESET << " on its back." << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "Red Ochre rock") != roomItems.end())
		{
			cout << "There is a pile of soft" << BOLDGREEN << " red rocks" << RESET << " on the ground." << endl;
		}	
	}

	// Pool of Water
	else if (currRoom->getName() == "Pool of Water")
	{
		cout << "A trail runs to the" << BOLDYELLOW << " east" << RESET << " toward what looks like a cave carved into one of the hills." << endl
			 << "Another trail runs to the" << BOLDYELLOW << " south" << RESET << " that leads ot a rock outcropping overlooking the water.." << endl
			 << "You can see through the crystal clear water and see the" << BOLDGREEN<< " fish" << RESET " swimming." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Fish") != roomItems.end())
		{
			cout << "There are a lot of " << BOLDGREEN << "fish " << RESET << " swimming in the water. Maybe I could find something to fish one out" << endl; 
		}
		if (find(roomItems.begin(), roomItems.end(), "Water Bottle") != roomItems.end())
		{
			cout << "You notice a small " << BOLDGREEN << "bottle " << RESET << "on the ground by the edge of the water." << endl
				 << "It looks like it is filled with water from the lake." << endl; 
		}
	}

	// Predator Den
	else if (currRoom->getName() == "Predator Den")
	{
		cout << "A trail runs to the" << BOLDYELLOW << " south" << RESET << " back toward the pool of water." << endl
			 << "Another trail runs to the" << BOLDYELLOW << " east" << RESET << " toward the cave." << endl;

		if (find(roomItems.begin(), roomItems.end(), "Rock with Spiral Symbol") != roomItems.end())
		{
			cout << "You see a small rock with a spiral symbol on it behind the predator." << endl
				 << "I wonder if I could distract him with something to grab the strange stone." << endl;
		}
	}

	// Tech Ruin
	else if (currRoom->getName() == "Tech Ruin")
	{
		cout << "What used to be large buildings long ago, appear half crumbling and falling apart." << endl
			 << "Some of these buildings appear to have once been a school, hospital, warehouse, and even some sort of civic center." << endl
			 << "The architecture is foreign to you, but some of the galaxy-wide accepted symbols are present." << endl
			 << "There is rubble and trash left from whoever built these buildings." << endl
			 << "A trail runs to the" << BOLDYELLOW << " north" << RESET << " back toward the field." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Aluminum Hook") != roomItems.end())
		{
			cout << "Among the rubble you see an" << BOLDGREEN << " aluminum hook" << RESET << " similar to a fishing hook." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Rock with Lightning Symbol") != roomItems.end())
		{
			cout << "You also spot a small" << BOLDGREEN << " rock with a lightning symbol" << RESET << " on it." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Old datapad") != roomItems.end())
		{
			cout << "There is an old "<< BOLDGREEN << "datapad" << RESET << " lying in the middle of the street." << endl;
		}

	}

	// Caves
	else if (currRoom->getName() == "Caves")
	{
		cout << "The entrance to the cave is covered by small string like vines." << endl
			 << "The trail runs" << BOLDYELLOW << " west" << RESET << " to the predator den and" 
			 << BOLDYELLOW << " east" << RESET << " to the field."<< endl
			 << "To the" << BOLDYELLOW << " north" << RESET << "is the pool of water."<< endl;
		if (magicDomeOpen)
		{
			cout << "Inside the cave to the" << BOLDYELLOW << " south" << RESET << "is the magic dome with the altar."<< endl;
		}
		else
		{
			cout << "There is a" << BOLDYELLOW << " door with strange writing" << RESET << " above it deeper within the cave to the" << BOLDYELLOW << " south" << RESET << endl;
		}
	}

	// Magic Dome
	else if (currRoom->getName() == "Magic Dome")
	{
		cout << "You see an " << BOLDYELLOW << "altar" << RESET << " with some strange writing on it. Tht altar has 3 slots on the top about the size of those strange rocks i've been seeing." << endl;
	}

	// Personal Cabin
	else if (currRoom->getName() == "Personal Cabin")
	{
		cout << "You are back on your ship in your personal cabin." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Picture of Family") != roomItems.end())
		{
			cout << "There is a picture of your family on the bedside table." << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "Old nadion emitter") != roomItems.end())
		{
			cout << "The old nadion emitter from the FTL engine lays on a shelf over your bed." << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "Strange Magic Circle") != roomItems.end())
		{
			cout << "There also is a strange magic circle that appeared on the ground below you." << endl;
		}
	}

	// Galley
	else if (currRoom->getName() == "Galley")
	{
		cout << "This is the galley where you usually take your meals." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Tools") != roomItems.end())
		{
			cout << "There are some assorted tools scattered on the table." << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "Nutrition Wafer Bar") != roomItems.end())
		{
			cout << "A nutrition wafer bar lays on the counter." << endl;
		}
	}

	// Engine Room 
	else if (currRoom->getName() == "Engine Room")
	{
		if (find(roomItems.begin(), roomItems.end(), "broken FTL engine") != roomItems.end())
		{
			cout << "Something chewed through the engine casing and pulled out the nadion emitter." << endl
				 << "A large amount of wiring was also pulled out that connects the nadion emitter to the photon splitter." << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "hammock") != roomItems.end())
		{
			cout << "My old hammock hangs between two poles." << endl;
		}
	}

	// The Head 
	else if (currRoom->getName() == "The Head")
	{
		cout << "" << endl;
		if (find(roomItems.begin(), roomItems.end(), "Rugvuk") != roomItems.end())
		{
			cout << "A Rugvuk seems to have escaped it's cage while you were planetside!" << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "pile of wiring") != roomItems.end())
		{
			cout << "You see the Rugvuk laying on the pile of wires it pulled out of the nadion emitter as a bed." << endl;
		}
	}

	// Med Bay
	else if (currRoom->getName() == "Med Bay")
	{
		cout << "The medical and science bay. " << endl
			 << "It contains basic first aid supplies, as well as small flora and fauna collected from previous expeditions." << endl;

		if (find(roomItems.begin(), roomItems.end(), "Empty Cage") != roomItems.end())
		{
			cout << "A few of the auto-feeding cages contain animals resting peacefully." << endl
				 << "You notice the door to one of the auto-feeding cages is wide open!" << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "Animal Sleeping pills") != roomItems.end())
		{
			cout << "There are some animal sleeping pills sitting next to the cages." << endl;
		}
	}

	// Armory
	else if (currRoom->getName() == "Armory")
	{
		cout << "This armory holds some self defense wepons to defend yourself during your travels." << endl;
		if (find(roomItems.begin(), roomItems.end(), "Stun Gun") != roomItems.end())
		{
			cout << "There is an animal stun gun on a rack. Looks like it still has a few charges." << endl;
		} 
		if (find(roomItems.begin(), roomItems.end(), "Deoderant") != roomItems.end())
		{
			cout << "Some deoderant is sitting in the locker." << endl;
		}
	}

	// Helm 
	else if (currRoom->getName() == "Helm")
	{
		cout << "" << endl;
		if (find(roomItems.begin(), roomItems.end(), "Scanning Console") != roomItems.end())
		{
			cout << "The scanning console allows you to scan planets and space around the ship." << endl;
		}
		if (find(roomItems.begin(), roomItems.end(), "Piloting Console") != roomItems.end())
		{
			if (!engineFixed)
			{
				cout << "The piloiting console sits as a blank screen..." << endl
				 	 << "The damage to the FTL engine must be causing the outage" << endl;
			}
			else if (engineFixed)
			{
				cout << "The piloiting console has power again. The ship is back online!" << endl;
			}
		}
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
	room * currRoom = player1->getLocation();

	// Knife
	if (currRoom->getName() == "Starting Room" && command[1] == "Knife with Runes")
	{ 
		cout << "It is a large knife, about 10 inches long. There are strange runes printed all over the blade." << endl;
	}
	// Bushes
	else if (currRoom->getName() == "Starting Room" && command[1] == "Thistle filled bushes")
	{
		cout << "The bushes are thick and you are unable to see through to the other side..." << endl
			 << "The thorns on the branches are long and look painful." << endl;
	}
	// Bag
	else if (currRoom->getName() == "Top of Tree" && command[1] == "Bag with Strange Runes")
	{
		cout << "It is a small bag with a clip that looks like its for your belt" << endl
			 << "There are runes printed all over the outside of the bag. They appear to match the ones seen on the knife below." << endl;
	}
	// Grazing animal
	else if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Grazing Animal with a strange stone on its back")
	{
		if(find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "The stone is round, smooth and has a sword like symbol on it. I bet I could take it without the animal knowing." << endl;
		}
		else
		{
			cout << "The animal is large, violet colored and roughly the size of horses from the planet Terra in the system of Sol." << endl
				 << "You notice what looks like a small round stone balanced on its back." << endl
				 << "If I was a little closer, maybe I could see what type of rock it is." << endl;
		}
	}
	// Red Ochre Rock
	else if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Red Ochre rock")
	{
		cout << "The red rocks on the ground look to be Red Ochre." << endl
			 << "They look soft and could probably be crushed into a powder." << endl;
	}
	// Aluminum Hook
	else if (currRoom->getName() == "Tech Ruins" && command[1] == "Aluminum Hook")
	{
		cout << "It is a small aluminum hook. It looks like it used to be used for fishing." << endl;
	}
	// Stone with Lightning Symbol
	else if (command[1] == "Stone with Lightning Symbol" && currRoom->getName() == "Tech Ruin")
	{
		cout << "It is a small smooth stone with a lighning symbol in the middle." << endl;
	}
	// Stone with Sword Symbol
	else if (command[1] == "Stone with Sword Symbol" && currRoom->getName() == "Field with Grazing Animals")
	{
		cout << "It is a small smooth stone with a sword symbol in the middle." << endl;
	}
	// Stone with Spiral Symbol
	else if (command[1] == "Stone with Spiral Symbol" && currRoom->getName() == "Predator Den")
	{
		if(predatorCounter == -1)
		{
			cout << "It is a small smooth stone with a spiral symbol in the middle." << endl;
		}
		else
		{
			predatorCounter++;
			if(predatorCounter == 1)
			{
				cout << "The predator growls loudly. Maybe you can distract him with something." << endl;
			}
			else if (predatorCounter == 2)
			{
				cout << "The predator stands up and threatens you with his large teeth. Maybe a distraction could save you from getting eaten." << endl;
			}
			else if (predatorCounter >= 3)
			{
				cout << "The predator lunges at you with a bloodthirsty roar. You have been eaten by the predator...." << endl << endl
					 << "GAME OVER!" << endl;
				exit (0);
			}
		}

	}
	//old datapad
	else if (currRoom->getName() == "Tech Ruins" && command[1] == "Old datapad")
	{
		cout << "It is an old datapad that was once owned by an inhabitant of the abandonded city." << endl
			 << "There is a note pulled up on the screen that reads:" << endl
			 << "'This planet is fighting and protecting itself every step of the way, as we try to colonize this planet." << endl
			 << "Whatever it is, it always tries to just scare us first before it attacks with any seriousness. " << endl
			 << "We've decided to just abandon this colony and go back to Zelon." << endl
			 << "Strange, as soon as we started packing up, all of our problems stopped, almost as if the planet wanted to help us leave quickly'" << endl;
	}
	// water bottle
	else if (currRoom->getName() == "Pool of Water" && command[1] == "Water Bottle")
	{
		cout << "It is a small bottle that looks to be filled with water." << endl;
	}
	// door
	else if (currRoom->getName() == "Caves" && command[1] == "Door with strange writing")
	{
		cout << "It is a large stone door with strange writing on it." << endl
			 << "As you're looking, the words magicaly change to read:" << endl
			 << "Blood of the Planet painted on this door gains you access to the stars." << endl;
	}
	// altar
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Altar")
	{

		cout << "On the altar, is a carving that, just like the door, translates itself to read:" << endl
			 << "On this altar, place the tokens of our people's progression." << endl
			 << "From warriors, to mages with an understanding of electricity," << endl
			 << "then finally one with the cosmos" << endl;
	}
	// slot 1
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Slot1")
	{
		cout << "This first slot has a sword symbol above it." << endl;

		if(find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Sword Symbol") != roomItems.end())
		{
			cout << "The stone with sword symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Lightning Symbol") != roomItems.end())
		{
			cout << "The stone with lightning symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Spiral Symbol") != roomItems.end())
		{
			cout << "The stone with spiral symbol is currently in this spot." << endl;
		}
		
	}
	// slot 2
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Slot2")
	{
		cout << "This second slot has a lightning symbol above it." << endl;

		if(find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Sword Symbol") != roomItems.end())
		{
			cout << "The stone with sword symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Lightning Symbol") != roomItems.end())
		{
			cout << "The stone with lightning symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Spiral Symbol") != roomItems.end())
		{
			cout << "The stone with spiral symbol is currently in this spot." << endl;
		}
	}
	// slot 3
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Slot3")
	{
		cout << "This third slot has a spiral symbol above it." << endl;

		if(find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Sword Symbol") != roomItems.end())
		{
			cout << "The stone with sword symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Lightning Symbol") != roomItems.end())
		{
			cout << "The stone with lightning symbol is currently in this spot." << endl;
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Spiral Symbol") != roomItems.end())
		{
			cout << "The stone with spiral symbol is currently in this spot." << endl;
		}
	}
	// picture of family
	else if (currRoom->getName() == "Personal Cabin" && command[1] == "Picture of Family")
	{
		cout << "You look at the picture of your family and it reminds you of home." << endl;
	}
	// old nadion emitter
	else if (currRoom->getName() == "Personal Cabin" && command[1] == "Old nadion emitter")
	{
		cout << "The old nadion emitter that was recently replaced in the FTL." << endl
			 << "It should still be functional, we just upgraded a few missions ago." << endl;
	}
	// strange magic circle
	else if (currRoom->getName() == "Personal Cabin" && command[1] == "Strange Magic Circle")
	{
		cout << "It is a strange magic circle that is glowing the same color as the teleportation circle on the altar." << endl;
	}
	// tools in galley
	else if (currRoom->getName() == "Galley" && command[1] == "Tools")
	{

		cout << "The tools on the table are from when I changed the nadion emitter a few weeks ago." << endl;
	}
	// nutrition wafer bar in galley
	else if (currRoom->getName() == "Galley" && command[1] == "Nutrition Wafer Bar")
	{
		cout << "It is a nutrition wafer bar I usually take with me to eat on the go." << endl;
	}
	// broken FTL Engine
	else if (currRoom->getName() == "Engine Room" && command[1] == "broken FTL engine")
	{
		if (engineFixed == true)
		{
			cout << "The FTL engine appears to be online." << endl;
		}
		else 
		{
			cout << "The FTL engine is offline." << endl
				 << "Something has chewed through the casing and pulled out the nadion emitter" << endl
				 << "It also has pulled a large amount of wiring that used to connect the nadion emitter to the photon splitter" << endl
				 << "If I remember right the old nadion emitter is in my cabin" << endl
				 << "and my tools are in the galley." << endl;
		}
		
	}
	else if (command[1] == "inventory")
	{
		inventoryCommand(command);
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
	// take stone in field
	else if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Stone with Sword Symbol")
	{
		if(find(currInventory.begin(), currInventory.end(), "Stone with Sword Symbol") != currInventory.end())
		{
			cout << "The  stone is already in your inventory..." << endl;
		}
		else if(sneakFlag == true)
		{
			cout << "You take the strange stone off the animals back and put it into your bag." << endl
				 << "The animal doesn't seem to be bothered. It just shakes and moves to a new patch of grass." << endl;

			currRoom->removeInteractable("Grazing Animal with a strange rock on its back");
			player1->addToInventory("Stone with Sword Symbol");
			currRoom->addInteractable("Grazing Animal");
		}
		else if (sneakFlag == false)
		{
			cout << "You are too far away to reach the stone... Try moving closer." << endl;
		}
	}
	// take stone in tech ruin
	else if (currRoom->getName() == "Tech Ruin" && command[1] == "Stone with Lightning Symbol")
	{
		if(find(currInventory.begin(), currInventory.end(), "Stone with Lightning Symbol") != currInventory.end())
		{
			cout << "You have already picked up the stone." << endl;
		}

		cout << "You pick up the stone with the lightning symbol and put it in your bag." << endl;
		player1->addToInventory("Stone with Lightning Symbol");
		currRoom->removeInteractable("Stone with Lightning Symbol");
	}
	// take stone in predator den
	else if (currRoom->getName() == "Predator Den" && command[1] == "Stone with Spiral Symbol")
	{
		if (find(currInventory.begin(), currInventory.end(), "Stone with Spiral Symbol") != currInventory.end())
		{
			cout << "You have already picked up the stone." << endl;
		}
		else if(predatorCounter == -1)
		{
			cout << "You take the stone while the predator is distracted with the fish and put it in your bag.";
			player1->addToInventory("Stone with Spiral Symbol");
		}
		else
		{
			predatorCounter++;
			if(predatorCounter == 1)
			{
				cout << "The predator growls loudly. Maybe you can distract him with something." << endl;
			}
			else if (predatorCounter == 2)
			{
				cout << "The predator stands up and threatens you with his large teeth. Maybe a distraction could save you from getting eaten." << endl;
			}
			else if (predatorCounter == 3)
			{
				cout << "The predator lunges at you with a bloodthirsty roar. You have been eaten by the predator...." << endl << endl
					 << "GAME OVER!" << endl;
				exit (0);

			}
		}
	}
	// take red rock
	else if(currRoom->getName() == "Field with Grazing Animals" && command[1] == "Red Ochre rock")
	{
		cout << "You pick up a soft red rock and put it in your bag." << endl;
		player1->addToInventory("Red Ochre rock");
		currRoom->removeInteractable("Red Ochre rock");
	}
	// take hook
	else if (currRoom->getName() == "Tech Ruin" && command[1] == "Aluminum Hook")
	{
		cout << "You pick up the aluminum hook and put it in your bag." << endl;
		player1->addToInventory("Aluminum Hook");
		currRoom->removeInteractable("Aluminum Hook");
	}
	// take vines
	else if (currRoom->getName() == "Caves" && command[1] == "string-like vines")
	{
		cout << "You pull down some of the string like vines and put it in your bag." << endl;
		player1->addToInventory("string-like vines");
		currRoom->removeInteractable("string-like vines");
	}
	// take branch
	else if (currRoom->getName() == "Top of Tree" && command[1] == "leafs filled branch")
	{
		if (find(currInventory.begin(), currInventory.end(), "Bag with Strange Runes") != currInventory.end())

		{
			cout << "You snap a long branch off of the tree and put it in your bag." << endl;
			player1->addToInventory("leafs filled branch");
			currRoom->removeInteractable("leafs filled branch");
		}
		else
		{
			cout << "You can't carry that branch and climb back down the tree! Maybe that strange bag would help." << endl;
		}
	}
	// take water bottle
	else if (currRoom->getName() == "Pool of Water" && command[1] == "Water Bottle")
	{
		cout << "You put the small bottle of water in your bag." << endl;
		player1->addToInventory("Water Bottle");
	}
	// take stone with sword symbol off altar
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Stone with Sword Symbol")
	{
		if(find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Sword Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot 1: Stone with Sword Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Sword Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot 2: Stone with Sword Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Sword Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot 3: Stone with Sword Symbol");
		}
	}
	// take stone with lightning symbol off altar
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Stone with Lightning Symbol")
	{
		if(find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Lightning Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot 1: Stone with Lightning Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Lightning Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot 2: Stone with Lightning Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Lightning Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot 3: Stone with Lightning Symbol");
		}
	}
	// take stone with spiral symbol off altar
	else if (currRoom->getName() == "Magic Dome" && command[1] == "Stone with Spiral Symbol")
	{
		if(find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Spiral Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot 1: Stone with Spiral Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Spiral Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot 2: Stone with Spiral Symbol");
		}
		else if (find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Spiral Symbol") != roomItems.end())
		{
			player1->addToInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot 3: Stone with Spiral Symbol");
		}
	}
	// take old nadion emitter
	else if (currRoom->getName() == "Personal Cabin" && command[1] == "Old nadion emitter")
	{
		cout << "You put the nadion emitter in your bag." << endl;
		player1->addToInventory("Old nadion emitter");
		currRoom->removeInteractable("Old nadion emitter");
	}
	// take tools
	else if (currRoom->getName() == "Galley" && command[1] == "Tools")
	{
		cout << "You put the tools in your bag." << endl;
		player1->addToInventory("Tools");
		currRoom->removeInteractable("Tools");
	}
	// take nutrition wafer bar
	else if (currRoom->getName() == "Galley" && command[1] == "Nutrition Wafer Bar")
	{
		cout << "You put the nutrition wafer bar in your bag." << endl;
		player1->addToInventory("Nutrition Wafer Bar");
		currRoom->removeInteractable("Nutrition Wafer Bar");
	}
	// take pile of wiring
	else if (currRoom->getName() == "The Head" && command[1] == "pile of wiring")
	{
		if(rugvukFlag)
		{
			cout << "You put the wires in your bag." << endl;
			player1->addToInventory("Wires");
			currRoom->removeInteractable("pile of wiring");
		}
		else
		{
			cout << "The Rugvuk lunges to bite you." << endl
				 << "Im gonna have to knock out this animal before I can take the wires" << endl;
		}
	}
	// take animal sleeping pills
	else if (currRoom->getName() == "Med Bay" && command[1] == "Animal Sleeping pills")
	{
		cout << "You put the animal sleeping pills in your bag." << endl;
		player1->addToInventory("Animal Sleeping pills");
		currRoom->removeInteractable("Animal Sleeping pills");
	}
	// take stun gun
	else if (currRoom->getName() == "Armory" && command[1] == "Stun Gun")
	{
		cout << "You put the stun gun in your bag." << endl;
		player1->addToInventory("Stun Gun");
		currRoom->removeInteractable("Stun Gun");
	}

	else
	{
		cout << "You cannot take that item" << endl;
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
			cout << "You cut the bushes using the knife with the strange runes to reveal the small lake to the west and the field to the east. \nOnly a pile of cut bushes remains." << endl;
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
	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Stone with Sword Symbol")
	{
		if (find(roomItems.begin(), roomItems.end(), "Sneak up on Animal") != roomItems.end())
		{
			cout << "You cut the strange stone off the animals back with your knife." << endl
				 << "The animal gets spooked and takes off running." << endl;
		}
		else
		{
			cout << " You are too far away to reach the stone... Try moving closer." << endl;
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

	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Grazing Animal with a strange stone on its back")
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

	if (currRoom->getName() == "Field with Grazing Animals" && command[1] == "Grazing Animal with a strange stone on its back")
	{
		cout << "You sneak up on the grazing animal with the strange stone on its back..." << endl
			 << "You notice the" << BOLDGREEN << " stone with sword symbol" << RESET << "is round and smooth ." << endl
			 << "If I'm careful I could probably grab the strange stone off the animals back." << endl;
		sneakFlag = true;
		currRoom->addInteractable("Sneak up on Animal");
	}

}

/******************************************************************************
** Function: putCommand()
** Description: processes the put command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::putCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<room*> adjacentRooms = player1->getAdjacentRooms();
	vector<string> roomItems = player1->getRoomItems();
	vector<string> currInventory = player1->getInventory();

	// put fishing pole in water
	if(currRoom->getName() == "Pool of Water")
	{
		if (find(command.begin(), command.end(), "Makeshift Fishing Pole") != command.end())
		{
			if(find(command.begin(), command.end(), "Water") != command.end())
			{
				cout << "You put the fishing pole in the water..." << endl
					 << "After a few minutes you feel a bite. You pull a large fish out of the water!" << endl
					 << "I bet this could distract the predator!" << endl
					 << "You put the fish in your bag" << endl;
				player1->addToInventory("Fish");
			}
		}
	}
	else if(currRoom->getName() == "Caves")
	{
		if (find(command.begin(), command.end(), "Red/Brown Paint") != command.end())
		{
			if (find(command.begin(), command.end(), "Door with strange writing") != command.end())
			{
				cout << "The heavy stone door slides open to reveal a large room." << endl;
				magicDomeOpen = true;

				// step into magic dome
				player1->setLocation(adjacentRooms[3]);
				currRoom = player1->getLocation();
				currRoom->printDescription();
				currRoom->visitRoom();
			}
		}
	}
	else if(currRoom->getName() == "Magic Dome" && find(command.begin(), command.end(), "Slot1") != command.end())
	{
		if (find(command.begin(), command.end(), "Stone with Sword Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Sword Symbol") != currInventory.end())
		{
			cout << "You place the stone with sword symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 1: Stone with Sword Symbol");
			player1->removeFromInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot1");
		}
		else if (find(command.begin(), command.end(), "Stone with Lightning Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Lightning Symbol") != currInventory.end())
		{
			cout << "You place the stone with lightning symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 1: Stone with Lightning Symbol");
			player1->removeFromInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot1");
		}
		else if(find(command.begin(), command.end(), "Stone with Spiral Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Spiral Symbol") != currInventory.end())
		{
			cout << "You place the stone with spiral symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 1: Stone with Spiral Symbol");
			player1->removeFromInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot1");
		}

		checkStones();
	}
	else if(currRoom->getName() == "Magic Dome" && find(command.begin(), command.end(), "Slot2") != command.end())
	{
		if (find(command.begin(), command.end(), "Stone with Sword Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Sword Symbol") != currInventory.end())
		{
			cout << "You place the stone with sword symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 2: Stone with Sword Symbol");
			player1->removeFromInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot2");
		}
		else if (find(command.begin(), command.end(), "Stone with Lightning Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Lightning Symbol") != currInventory.end())
		{
			cout << "You place the stone with lightning symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 2: Stone with Lightning Symbol");
			player1->removeFromInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot2");
		}
		else if(find(command.begin(), command.end(), "Stone with Spiral Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Spiral Symbol") != currInventory.end())
		{
			cout << "You place the stone with spiral symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 2: Stone with Spiral Symbol");
			player1->removeFromInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot2");
		}

		checkStones();
	}
	else if(currRoom->getName() == "Magic Dome" && find(command.begin(), command.end(), "Slot3") != command.end())
	{
		if (find(command.begin(), command.end(), "Stone with Sword Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Sword Symbol") != currInventory.end())
		{
			cout << "You place the stone with sword symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 3: Stone with Sword Symbol");
			player1->removeFromInventory("Stone with Sword Symbol");
			currRoom->removeInteractable("Slot3");
		}
		else if (find(command.begin(), command.end(), "Stone with Lightning Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Lightning Symbol") != currInventory.end())
		{
			cout << "You place the stone with lightning symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 3: Stone with Lightning Symbol");
			player1->removeFromInventory("Stone with Lightning Symbol");
			currRoom->removeInteractable("Slot3");
		}
		else if(find(command.begin(), command.end(), "Stone with Spiral Symbol") != command.end() && find(currInventory.begin(), currInventory.end(), "Stone with Spiral Symbol") != currInventory.end())
		{
			cout << "You place the stone with spiral symbol in the first slot in the altar." << endl;
			currRoom->addInteractable("Slot 3: Stone with Spiral Symbol");
			player1->removeFromInventory("Stone with Spiral Symbol");
			currRoom->removeInteractable("Slot3");
		}

		checkStones();
	}
	
}

/******************************************************************************
** Function: checkStones()
** Description: Helper functionthat checks the altar stones are in correct 
**			    position
** Parameters: None
** Returns: None
*******************************************************************************/
void game::checkStones()
{
	room * currRoom = player1->getLocation();
	vector<string> roomItems = player1->getRoomItems();
	vector<room*> adjacentRooms = player1->getAdjacentRooms();

	if (find(roomItems.begin(), roomItems.end(), "Slot 1: Stone with Sword Symbol") != roomItems.end() && find(roomItems.begin(), roomItems.end(), "Slot 2: Stone with Lightning Symbol") != roomItems.end() && find(roomItems.begin(), roomItems.end(), "Slot 3: Stone with Spiral Symbol") != roomItems.end())
	{
		cout << "A you place the last rock in the altar, it begins releasing dancing waves of light." << endl
			 << "They completly engulf you as you begin to become weightless." << endl;
		// teleport back to ship
		for (int i = 0; i < (int)adjacentRooms.size(); i++)
		{
			if (adjacentRooms[i]->getName() == "Personal Cabin") 
			{
				player1->setLocation(adjacentRooms[i]);
				currRoom = player1->getLocation();
				currRoom->printDescription();
				currRoom->visitRoom();
				break;
			}
		} 
	}
}

/******************************************************************************
** Function: dropCommand()
** Description: processes the drop command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::dropCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();
	if(command[1] == "Fish")
	{
		if (find(currInventory.begin(), currInventory.end(), "Fish") != currInventory.end())
		{
			cout << "You drop the fish on the ground" << endl;
			if(currRoom->getName() == "Predator Den")
			{
				cout << "The predator gets distracted and begins eatting the fish." << endl
					 << "He gets distracted and forgets about the strange stone in his den." << endl
					 << "I could probably grab it while he is eating." << endl;
				predatorCounter = -1;
			}
			else
			{
				cout << "You drop the fish on the ground." << endl;
				player1->removeFromInventory("Fish");
				currRoom->addInteractable("Fish");
			}
		}
		else
		{
			cout << "You do not have a fish in your inventory..." << endl;
		}
	}
}

/******************************************************************************
** Function: crushCommand()
** Description: processes the crush command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::crushCommand(vector<string> command)
{
	//room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	if(command[1] == "Red Ochre rock" && find(currInventory.begin(), currInventory.end(), "Red Ochre rock") != currInventory.end())
	{
		cout << "The Red Ochre rock is crushed down into a fine powder." << endl;
		player1->removeFromInventory("Red Ochre rock");
		player1->addToInventory("Crushed Red Ochre");
	}
}

/******************************************************************************
** Function: combineCommand()
** Description: processes the combine command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::combineCommand(vector<string> command)
{
	vector<string> currInventory = player1->getInventory();

	// combine water and red ochre to make paint
	if(find(command.begin(), command.end(), "Water") != command.end()) 
	{
		if(find(command.begin(), command.end(), "Red Ochre rock") != command.end())
		{
			if(find(currInventory.begin(), currInventory.end(), "Crushed Red Ochre") != currInventory.end())
			{
				if(find(currInventory.begin(), currInventory.end(), "Water Bottle") != currInventory.end())
				{
					cout << "You put some of the crushed Red Ochre into the water bottle and shake it up to create a red/brown paint";
					player1->removeFromInventory("Crushed Red Ochre");
					player1->removeFromInventory("Water Bottle");
					player1->addToInventory("Red/Brown Paint");
				}
				else
				{
					cout << "You do not have the water bottle in your inventory." << endl;
				}
			}
			else
			{
				cout << "You do not have Red Ochre in your inventory." << endl;
			}
		}
	}

	// make fishing pole
	if(find(command.begin(), command.end(), "leafs filled branch") != command.end() && find(command.begin(), command.end(), "string-like vines") != command.end() && find(command.begin(), command.end(), "Aluminum Hook") != command.end() && find(currInventory.begin(), currInventory.end(), "Aluminum Hook") != currInventory.end())
	{
		if(find(currInventory.begin(), currInventory.end(), "leafs filled branch") != command.end())
		{
			if( find(currInventory.begin(), currInventory.end(), "string-like vines") != currInventory.end()) 
			{
				if(find(command.begin(), command.end(), "Aluminum Hook") != command.end() && find(currInventory.begin(), currInventory.end(), "Aluminum Hook") != currInventory.end()) 
				{
					cout << "You combine the branch, string-like vines and hook to create a makeshift fishing pole." << endl;
					player1->removeFromInventory("leafs filled branch");
					player1->removeFromInventory("string-like vines");
					player1->removeFromInventory("Aluminum Hook");
					player1->addToInventory("Makeshift Fishing Pole");
				}
				else
				{
					cout << "You do not have the aluminum hook in your inventory." << endl;
				}
			}
			else 
			{
				cout << "You do not have the string-like vines in your inventory." << endl;
			}
		}
		else
		{
			cout << "You do not have the branch in your inventory." << endl;
		}
	}

	// combine sleeping pills and wafer
	if(find(command.begin(), command.end(), "Animal Sleeping pills") != command.end()) 
	{
		if(find(command.begin(), command.end(), "Nutrition Wafer Bar") != command.end())
		{
			if(find(currInventory.begin(), currInventory.end(), "Animal Sleeping pills") != currInventory.end())
			{
				if(find(currInventory.begin(), currInventory.end(), "Nutrition Wafer Bar") != currInventory.end())
				{
					cout << "You combine the animal sleeping pills and the nutrition wafer bar to make a medicated wafer." << endl
						 << "I bet it could knock out the Rugvuk." << endl;
					player1->removeFromInventory("Animal Sleeping pills");
					player1->removeFromInventory("Nutrition Wafer Bar");
					player1->addToInventory("Medicated Wafer");
				}
			}
		}
	}
		
}

/******************************************************************************
** Function: giveCommand()
** Description: processes the give command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::giveCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	if (currRoom->getName() == "The Head" && command[1] == "Nutrition Wafer Bar")
	{
		if (find(currInventory.begin(), currInventory.end(), "Medicated Wafer") != currInventory.end())
		{
			cout << "You give the medicated wafer to the Rugvk." << endl
				 << "The Rugvk lays down and closes his eyes. It looks like the sleeping pills worked." << endl;
			rugvukFlag = true;
			player1->removeFromInventory("Medicated Wafer");
		}
	}

}

/******************************************************************************
** Function: useCommand()
** Description: processes the use command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::useCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	if (currRoom->getName() == "The Head" && command[1] == "Stun Gun")
	{
		if (find(currInventory.begin(), currInventory.end(), "Stun Gun") != currInventory.end())
		{
			cout << "You use the stun gun to stun the Rugvk." << endl
				 << "It gets knocked out and falls limp to the ground." << endl;
			rugvukFlag = true;
		}
	}
	else if (currRoom->getName() == "Helm" && command[1] == "Piloting Console")
	{
		if (engineFixed)
		{
			cout << "You select your destination, and the ship takes off toward your next adventure." << endl;
			exit (0);
		}
		else
		{
			cout << "The console is dark. Looks like the FTL engine is offline" << endl;
		}
	}
	else if (currRoom->getName() == "Helm" && command[1] == "Scanning Console")
	{
		
	}

}

/******************************************************************************
** Function: fixCommand()
** Description: processes the fix command sent from the parser
** Parameters: Vector of parsed commands
** Returns: None
*******************************************************************************/
void game::fixCommand(vector<string> command)
{
	room * currRoom = player1->getLocation();
	vector<string> currInventory = player1->getInventory();

	// fix engine
	if(find(command.begin(), command.end(), "broken FTL engine") != command.end() && currRoom->getName() == "Engine Room") 
	{
		if(find(currInventory.begin(), currInventory.end(), "Tools") != currInventory.end())
		{
			if(find(currInventory.begin(), currInventory.end(), "Old nadion emitter") != currInventory.end())
			{
				if(find(currInventory.begin(), currInventory.end(), "Wires") != currInventory.end())
				{

					cout << "You fix the engine by re-intsalling the nadion emitter and splicing the wires back toghether." << endl;
					player1->removeFromInventory("Old nadion emitter");
					player1->removeFromInventory("Wires");
					engineFixed = true;
				}
				else
				{
					cout << "You do not have the wiring in your inventory" << endl;
				}
			}
			else
			{
				cout << "You do not have the old nadion emitter in your inventory" << endl;
			}
		}
		else
		{
			cout << "You do not have any tools in your inventory" << endl;
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

 /******************************************************************************
 ** Function: setRooms()
 ** Description: sets player 
 ** Parameters: point to a player
 ** Returns: None
 ******************************************************************************/
void game::setPlayers(player* p1){

	player1 = p1;
}


