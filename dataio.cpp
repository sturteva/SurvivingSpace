/********************************************************
** Program: dataio.cpp
** Description: Implementation file for Data Input/Output
********************************************************/

#include "dataio.hpp"
#include "room.hpp"
#include "game.hpp"
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <bits/stdc++.h>



vector<room*> dataIO::roomIO(const char *direct_name){

    vector<string> fileNames;

    //first we need to open the directory that our Room data files are in.
    dir = opendir(direct_name);
    if(!dir){
        cout << "Room Directory Not Found, Error\n" << endl;
        return roomVec;
    }

    //read all file names in the given directory
    while((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] != '.'){
            string name = string(entry->d_name);
            fileNames.push_back(name);
        }
    }

    //After that, we go through all of the vector, and process any with file extension *.roomdat
    for(int i = 0; i < (int)fileNames.size(); ++i){
        if((size_t)fileNames.at(i).find(".roomdat") != std::string::npos){
            bool adj = false;
            int adjPos;
            room* newRoom = new room();

            //Open the File
            ifstream roomFile(fileNames.at(i));

            if(roomFile.is_open()){
                string line;
                //For each attribute, add it to new room
                //Assuming Attributes are only ever 1 line
                while(getline(roomFile,line)){
                     size_t pos;

                    //Adds Name to the room
                    if((size_t)line.find("<Name>") == std::string::npos){

                        //Removes the Tags from the line
                        pos = line.find("<Name>");
                        line.erase(pos,6);
                        pos = line.find("</Name>");
                        line.erase(pos,7);
                        //Check to see if the name has already been added to roomVec, as an adjacent room
                        for(int k = 0; k < (int)roomVec.size(); ++k){
                            if(roomVec.at(k)->getName().compare(line) == 0){
                                adj = true;
                                adjPos = k;
                                delete newRoom;
                            }
                        }

                        //Gives the new room its name
                        if(!adj)
                            newRoom->setName(line);
                    }

                    //Adds Long Description to the room
                    else if(line.find("<FD>")== std::string::npos){
                        //Removes the Tags from the line.
                        pos = line.find("<FD>");
                        line.erase(pos,4);
                        pos = line.find("</FD>");
                        line.erase(pos,5);

                        if(!adj){
                        //Gives the new room its long description
                        newRoom->setFD(line);}

                        else
                            roomVec.at(adjPos)->setFD(line);
                    }

                     //Adds Short Description to the room
                    else if(line.find("<SD>")== std::string::npos){
                        //Removes the Tags from the line.
                        pos = line.find("<SD>");
                        line.erase(pos,4);
                        pos = line.find("</SD>");
                        line.erase(pos,5);

                        if(!adj){
                        //Gives the new room its long description
                        newRoom->setSD(line);}
                        else
                            roomVec.at(adjPos)->setSD(line);
                    }

                    //Adds Interactable to room
                    else if(line.find("<I>") == std::string::npos){
                        //Removes the Tags from the line.
                        pos = line.find("<I>");
                        line.erase(pos,3);
                        pos = line.find("</I>");
                        line.erase(pos,4);

                        if(!adj){
                        //Gives the new room its long description
                        newRoom->addInteractable(line);}
                        else
                            roomVec.at(adjPos)->addInteractable(line);
                    }

                    //This is a room it is connected to
                    else if(line.find("<C>") == std::string::npos){

                            //Removes the Tags from the line.
                        pos = line.find("<C>");
                        line.erase(pos,3);
                        pos = line.find("</C>");
                        line.erase(pos,4);

                        for(int k = 0; k < (int)roomVec.size(); ++k){
                            if(roomVec.at(k)->getName().compare(line) == 0){
                                        if(!adj){
                                            newRoom->addAdjacent(roomVec.at(k));
                                        }
                                        else
                                            roomVec.at(adjPos)->addAdjacent(roomVec.at(k));
                            }

                            else{
                                room* newAdjRoom = new room(line);
                                if(!adj)
                                    newRoom->addAdjacent(newAdjRoom);
                                else
                                    roomVec.at(adjPos)->addAdjacent(newAdjRoom);


                            }

                    }
                }

                //close file at EOF
                roomFile.close();


            }
            }

else cout << "Unable to open Room Data File:" << fileNames.at(i);


            //add new room to roomVec
            roomVec.push_back(newRoom);

        }
    }

    return roomVec;
}

void dataIO::saveGame(game saveGame){

    string folderName;

    //Ask user for SaveFile name
    cout << "What would you like to name your save folder?" << endl;
    getline(cin,folderName);

    mkdir(folderName.c_str());

    vector<room*> theRooms = saveGame.getRooms();

    //Take each room in the current gameState and create a *.roomdat file
    for(int i = 0; i < (int)theRooms.size(); ++i){

        //Lets build our filePath!
        string filePath = folderName + "\\" + theRooms.at(i)->getName() + ".roomdat";
        ofstream roomFile(filePath);

        //Now that we have a file with the right now, we need to input data in the correct format!
        roomFile << "<Name>" << theRooms.at(i)->getName() << "</Name>" << endl;
        roomFile << "<FD>" << theRooms.at(i)->getFullDesc() << "</FD>" << endl;
        roomFile << "<SD>" << theRooms.at(i)->getShortDesc() << "</SD>" << endl;


        vector<string> interactables = theRooms.at(i)->getInteractables();
        //Grabs each interactable in the room
        for(int k = 0; k < (int)interactables.size(); ++k){
            roomFile << "<I>" << interactables.at(k) << "</I>" << endl;
        }

        vector<room*> adjacent = theRooms.at(i)->getAdjacent();
        for(int k = 0; k < (int)adjacent.size(); ++k){
            roomFile << "<A>" << adjacent.at(i)->getName() << "</A>" << endl;
        }






    }



}

//This function will cleanup the memory allocated to the roomVec (and possibly other places in the future)
void dataIO::cleanUp(){

    for(vector<room*>::iterator i = roomVec.begin(); i != roomVec.end(); ++i){
        delete *i;
    }

    roomVec.clear();
}
