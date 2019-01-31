/********************************************************
** Program: game.hpp
** Description: Header file for game class.
********************************************************/
#ifndef GAME_HPP
#define GAME_HPP

#include "room.hpp"
#include "player.hpp"

class game
{
	private:  
    	player * player1;
    	room * rooms[];

	public:
		game();
		void initlizeRooms();
        void start();
    
};

#endif