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

using namespace std;

class dataIO{

    private:
            DIR *dir;
            struct dirent *entry;

    public:
        vector<room> roomIO(char*); // Will return a vector full of newly created rooms from our data files.

};
#endif
