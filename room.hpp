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
    	room *next;
    	bool visited;

	public:
	    room();
        room(string, room *);
        string getName();
        void setName(string);
        void printDescription();

};

#endif
