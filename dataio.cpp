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
#include <fstream>
#include <stdio.h>

vector<room> dataIO::roomIO(char *direct_name){

    vector<string> fileNames;
    vector<room> roomVec; //empty vector of rooms

    //first we need to open the directory that our Room data files are in.
    dir = opendir(direct_name);
    if(!dir){
        cout << "Room Directory Not Found, Error\n" << endl;
        return NULL;
    }

    //read all file names in the given directory
    while((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] != '.'){
            string name = string(entry->d_name);
            fileNames.push_back(name);
        }
    }

    //After that, we go through all of the vector, and process any with file extension *.roomdat
    for(int i = 0; i < fileNames.size(); ++i){
        if(fileNames.at(i).find(".roomdat") != std::string::npos){
            room newRoom;

            //Open the File
            ifstream roomFile(fileNames.at(i));

            if(roomFile.is_open()){
                string line;
                //For each attribute, add it to new room
                //Assuming Attributes are only ever 1 line
                while(getline(roomFile,line)){
                     size_t pos;
                    if(line.find("<Name>")){

                        //Removes the Tags from the line
                        pos = line.find("<Name>");
                        line.erase(pos,6);
                        pos = line.find("</Name>");
                        line.erase(pos,7);

                        //Gives the new room its name
                        newRoom.setName(line);

                    }
                }

                //close file at EOF
                roomFile.close();
            }
            else cout << "Unable to open Room Data File:" << fileNames.at(i);



            //add new room to roomVec
            roomVec.push_back(newRoom);

        }
    }



    return roomVec;
}
