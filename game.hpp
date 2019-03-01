/********************************************************
** Program: game.hpp
** Description: Header file for game class.
********************************************************/
#include "room.hpp"
#include "player.hpp"
#include "dataio.hpp"


using std::vector;

#ifndef GAME_HPP
#define GAME_HPP

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
	    void doCommand(vector<string>);
	    void helpCommand(vector<string>);
	    void saveCommand(vector<string>);
	    void goCommand(vector<string>);
	    void lookCommand(vector<string>);
	    void inventoryCommand(vector<string>);
	    void takeCommand(vector<string>);
	    void cutCommand(vector<string>);
	    void moveTowardCommand(vector<string>);
	    void sneakCommand(vector<string>);
	    vector<room*> getRooms();
	    player* getPlayer1();
	    int getNumPlayers();
	    void setRooms(vector<room*>);

};

#endif
