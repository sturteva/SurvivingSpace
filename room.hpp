/********************************************************
** Program: room.hpp
** Description: Header file for room class.
********************************************************/
using namespace std;
#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>
#include <vector>
class room
{
	private:
    	string name;
    	string fullDesc;
    	string shortDesc;
    	vector<string> interactables;
    	vector<room*> adjacent;
    	bool visited;

	public:

	    room();
      room(string, room *);
      room(string);
      string getName();
      string getFullDesc();
      string getShortDesc();
      vector<string> getInteractables();
      vector<room*> getAdjacent();
      void setName(string);
      void setFD(string);
      void setSD(string);
      void addInteractable(string);
      void addAdjacent(room*);
      void printDescription();

};

#endif
