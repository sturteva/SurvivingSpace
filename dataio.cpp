/********************************************************
** Program: dataio.cpp
** Description: Implementation file for Data Input/Output
********************************************************/

#include "dataio.hpp"
#include "room.hpp"
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <stdio.h>

vector<room> dataIO::roomIO(char *direct_name){

    vector<string> fileNames;
    vector<room> roomVec; //empty vector of rooms

    //first we need to open the directory that our Room data files are in.
    dir = opendir(direct_name);
    if(!dir){
        cout << "Room Directory Not Found, Error\n" << endl;
        return 0;
    }

    //read all file names in the given directory
    while((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] != '.'){
            string name = string(entyr->d_name);
            fileNames.push_back(name);
        }
    }

    //After that, we go through all of the vector, and process any with file extension *.roomdat
    for(int i = 0; i < fileNames.size(); ++i){
        if(fileNames.at(i).find(".roomdat") != std::string::npos){
            //create new room
            //Open the file
            //For each attribute, add it to new room
            //close file at EOF
            //add new room to roomVec

        }
    }



    return roomVec;
}
