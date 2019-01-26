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
	
}


/********************************************************
 ** Function: initlize ()
 ** Description: initilizes the gamestate
 ** Parameters: None
 ********************************************************/
void game::initlize(room * startRoom)
{
	player1.setLocation(startRoom);
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

	cout << "Welcome to our Text Adventure!" << endl << endl;

	do
	{
		currRoom = player1.getLocation();
		currRoom->printDescription();

		// ask for player input
		cout << "What would you like to do? (Type \"exit\" to stop adventure) ";
		cin >> command;
		cout << endl;
	}while (command != "exit");
	

}