/********************************************************
** Program: dataio.hpp
** Description: Header file for Data Input/Output
********************************************************/
#ifndef DATAIO_HPP
#define DATAIO_HPP

#include "room.hpp"

#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <stdio.h>

using std::vector;
using std::string;

class game; //Forward declaring game

class dataIO{

    private:
            DIR *dir;
            struct dirent *entry;
            vector<room*> roomVec;

    public:
        vector<room*> roomIO(string); // Will return a vector full of newly created rooms from our data files.
        void saveGame(game);
        game loadGame(string);
        void cleanUp();

};
#endif
