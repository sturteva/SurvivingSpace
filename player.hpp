/********************************************************
** Program: player.hpp
** Description: Header file for player class.
********************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP

class room;

class player
{
	private:  
    	room* location;

	public:
        player();
        room* getLocation();
        void setLocation(room *room);
    
};

#endif