/********************************************************
** Program: game.cpp
** Description: Implemenation file for game class.
********************************************************/
using namespace std;
#include "game.hpp"
#include "room.hpp"
#include "player.hpp"
#include <string>
#include <iostream>


/********************************************************
 ** Function: game ()
 ** Description: constructor
 ** Parameters: None
 ********************************************************/
game::game()
{
	player1 = new player();
}


/********************************************************
 ** Function: initlize ()
 ** Description: initilizes the gamestate
 ** Parameters: None
 ********************************************************/
void game::initlizeRooms()
{
	//initilize rooms with files
	rooms[0] = new room("startLocation");



	player1->setLocation(rooms[0]);
}

 /********************************************************
 ** Function: start()
 ** Description: constructor
 ** Parameters: None
 ********************************************************/
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
	}while (command != "exit");
	

}
