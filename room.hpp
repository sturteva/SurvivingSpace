/********************************************************
** Program: room.hpp
** Description: Header file for room class.
********************************************************/
using namespace std;
#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>

class room
{
	private:  
    	string name;
    	string fullDesc;
    	string shortDesc;
    	string interactables[];
    	room *adjacent;
    	bool visited;

	public:
        room(string);
        string getName();
        void printDescription();
       
};

#endif