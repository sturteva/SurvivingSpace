/********************************************************
** Program: player.hpp
** Description: Header file for player class.
********************************************************/
#include "inventory.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP


class room;


class player
{
	private:  
    	room* location;
    	inventory playerInventory;

	public:
        player();
        room* getLocation();
        void setLocation(room *room);
    
};

#endif