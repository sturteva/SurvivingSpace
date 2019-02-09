/********************************************************
** Program: game.hpp
** Description: Header file for game class.
********************************************************/
#ifndef GAME_HPP
#define GAME_HPP

#include "room.hpp"
#include "player.hpp"
#include "dataio.hpp"

class dataIO; //forward declaring

class game
{
	private:
    	player * player1;
    	vector<room*> rooms;
    	dataIO ourData;
    	int numPlayers;

	public:
		game();
		void initializeRooms();
		void initializeDict();
	    void start();
	    vector<room*>getRooms();
	    player* getPlayer1();
	    int getNumPlayers();
	    void setRooms(vector<room*>);

};

#endif
