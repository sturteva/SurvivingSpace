/*******************************************************************************
** Program: dataio.cpp
** Description: Implementation file for Data Input/Output
*******************************************************************************/
#include "dataio.hpp"
#include "room.hpp"
#include "game.hpp"
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

/******************************************************************************
** Function: roomIO()
** Description: Loads room vector using roomdat files
** Parameters: string
*******************************************************************************/
vector<room*> dataIO::roomIO(string direct_name){

    vector<string> fileNames;

    //DEBUG
    //cout << "Directory Name: " << direct_name << endl;

    //first we need to open the directory that our Room data files are in.
    dir = opendir(direct_name.c_str());
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
            
            room* newRoom;

		//build full filename
		string theFile =  direct_name + "/" + fileNames.at(i);

		//DEBUG LINE
		//cout << "full file name: " << theFile << endl;
            //Open the File
            ifstream roomFile(theFile.c_str());


            if(roomFile.is_open()){

		string line;
                //For each attribute, add it to new room
                //Assuming Attributes are only ever 1 line
                while(getline(roomFile,line)){



			
                     size_t pos;

                    //Adds Name to the room
                    if(line.find("<Name>") != std::string::npos){

			//Debug
			//cout << "inside <NAME>" << endl;

                        //Removes the Tags from the line
                        pos = line.find("<Name>");

			line.erase(pos,6);

			pos = line.find("</Name>");
                        line.erase(pos,7);
                        //Check to see if the name has already been added to roomVec, as an adjacent room
                        for(int k = 0; k < (int)roomVec.size(); ++k){
                            if(roomVec.at(k)->getName().compare(line) == 0){
                                adj = true;
                                
                                newRoom = roomVec.at(k);
                            }
                        }
			//Debug
			//cout << "After erasing:" << line << endl;
                        //Gives the new room its name
                        if(!adj)
			    newRoom = new room();
                            newRoom->setName(line);
                    }

                    //Adds Long Description to the room
                    else if(line.find("<FD>")!= std::string::npos){

			//Debug
			//cout << "Inside <FD>" << endl;
                        //Removes the Tags from the line.
                        pos = line.find("<FD>");
                        line.erase(pos,4);
                        pos = line.find("</FD>");
                        line.erase(pos,5);

                        
                        //Gives the new room its long description
                        newRoom->setFD(line);

			}
                      
                    

                     //Adds Short Description to the room
                    else if(line.find("<SD>")!= std::string::npos){

			//Debug
			//cout << "Inside <SD>" << endl;
                        //Removes the Tags from the line.
                        pos = line.find("<SD>");
                        line.erase(pos,4);
                        pos = line.find("</SD>");
                        line.erase(pos,5);

                        //Gives the new room its long description
                        newRoom->setSD(line);
                        
                    }

                    //Adds Interactable to room
                    else if(line.find("<I>") != std::string::npos){

			//debug
			//cout << "Inside <I>" << endl;

                        //Removes the Tags from the line.
                        pos = line.find("<I>");
                        line.erase(pos,3);
                        pos = line.find("</I>");
                        line.erase(pos,4);

                        
                        //Gives the new room its long description
                        newRoom->addInteractable(line);
                    }

                    //This is a room it is connected to
                    else if(line.find("<C>") != std::string::npos){

			//Debug
			//cout << "Inside <C>" << endl;
		        //Removes the Tags from the line.
                        pos = line.find("<C>");
                        line.erase(pos,3);
                        pos = line.find("</C>");
                        line.erase(pos,4);
			
			bool foundAdj = false;
                        for(int k = 0; k < (int)roomVec.size(); ++k){

				
				
                            if(roomVec.at(k)->getName().compare(line) == 0){
                                  
                                 
                                            newRoom->addAdjacent(roomVec.at(k));
					    foundAdj = true;
					break;
                                        
                            }
                       }

			if(!foundAdj){
				room* newAdj = new room(line);
				newRoom->addAdjacent(newAdj);			

			}

                    }
                

                
                


            }//END of WHILE loop

		roomFile.close();
            }//END checking if file is open

else cout << "Unable to open Room Data File:" << fileNames.at(i) << endl;

            //add new room to roomVec
            roomVec.push_back(newRoom);

        }
    }

//Debug
/*for(int j = 0; j < (int)roomVec.size(); ++j){

	cout << "ROOM NAME: " << roomVec.at(j)->getName() << endl;
	vector<room*> adjRooms = roomVec.at(j)->getAdjacent();
	for(int m = 0; m < (int)adjRooms.size(); ++m){
		cout << "Ajacent:  " <<adjRooms.at(m)->getName() << endl;
	}
}*/

    return roomVec;
}

/******************************************************************************
** Function: saveGame()
** Description: Saves game state and all rooms to a new save folder
** Parameters: game object to be saved
*******************************************************************************/
void dataIO::saveGame(game saveGame){

    if(saveGame.getNumPlayers() > 1){
        cout << "You are only allowed to save games in a Single Player Adventure" << endl;
        return;
    }

    string folderName;
    //Ask user for SaveFile name
    cout << "What would you like to name your save folder?" << endl;
    getline(cin,folderName);

    mkdir(folderName.c_str(), 0666);

    vector<room*> theRooms = saveGame.getRooms();

    //Take each room in the current gameState and create a *.roomdat file
    for(int i = 0; i < (int)theRooms.size(); ++i){

        //Lets build our filePath!
        string filePath = folderName + "\\" + theRooms.at(i)->getName() + ".roomdat";
        ofstream roomFile(filePath.c_str());

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

        roomFile.close();

    }

    //After that is saved, we will save player information




}

/******************************************************************************
** Function: loadGame()
** Description: Loads game state from existing save folder
** Parameters: name of save folder
*******************************************************************************/
game dataIO::loadGame(string folderName){

    //Here is where we will create a new Gamesate, first pulling the room data
    game newGame;
    vector<room*> loadedRooms = roomIO(folderName.c_str());
    newGame.setRooms(loadedRooms);

    //Need to set the player stuff

    return newGame;

}

/******************************************************************************
** Function: cleanUp()
** Description: Frees all memory allocated for dataIO
** Parameters: None
*******************************************************************************/
void dataIO::cleanUp(){

    for(vector<room*>::iterator i = roomVec.begin(); i != roomVec.end(); ++i){
        delete *i;
    }

    roomVec.clear();
}
