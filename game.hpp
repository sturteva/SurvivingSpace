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
    	player player1;

	public:
		game();
		void initlize(room*);
        void start();
    
};

#endif