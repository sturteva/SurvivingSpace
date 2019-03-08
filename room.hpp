/********************************************************
** Program: room.hpp
** Description: Header file for room class.
********************************************************/
#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>
#include <vector>

using std::string;
using std::vector;

class room
{
	private:
    	string name;
    	string fullDesc;
    	string shortDesc;
    	vector<string> interactables;
    	vector<room*> adjacent;
	vector<string> adjDir;
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
      vector<string> getAdjDir();
      bool getVisited();
      void setName(string);
      void setFD(string);
      void setSD(string);
      void addInteractable(string);
      void addAdjDir(string);
      void removeInteractable(string);
      void addAdjacent(room*);
      void printDescription();
      void printRoomInfo();
      void visitRoom();

};

#endif
