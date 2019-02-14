/********************************************************
** Program: player.hpp
** Description: Header file for player class.
********************************************************/
#include "inventory.hpp"

using std::vector;

#ifndef PLAYER_HPP
#define PLAYER_HPP


class room;


class player
{
	private:  
    	room* location;
    	vector<string> playerInventory;

	public:
        player();
        room* getLocation();
        void setLocation(room *room);
        vector<room*> getAdjacentRooms();
        vector<string> getRoomItems();
        void addToInventory(string);
        vector<string> getInventory();


    
};

#endif