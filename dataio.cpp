/*******************************************************************************
** Program: dataio.cpp
** Description: Implementation file for Data Input/Output
*******************************************************************************/
#include "dataio.hpp"
#include "room.hpp"
#include "game.hpp"
#include "player.hpp"
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

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


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
						
		/*	line.insert(5,BOLDRED);
			line.insert((int)line.length()-6,RESET);
			cout << "OTHER TEST HERE" << endl;
			cout << line << endl;*/

			
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



                            if(roomVec.at(k)->getName() == line){


                                newRoom->addAdjacent(roomVec.at(k));
				foundAdj = true;
				break;

                            }
                       }

			if(!foundAdj){


				room* newAdj = new room(line);
				newRoom->addAdjacent(newAdj);
				newAdj->addAdjacent(newRoom);
				roomVec.push_back(newAdj);

				//Debug
				//cout << "New Adj Name: " << newAdj->getName() << endl;

			}

                    }

		//Mostly for Saved Games...if the room has been visited before
		else if(line.find("<V>") != std::string::npos){
			newRoom->visitRoom();

		}

		//If there is a KeyWord, we will be finding that keyword, and then
		//Adding some color
		else if(line.find("<KW>") != std::string::npos){
		
	 		pos = line.find("<KW>");
                        line.erase(pos,4);
                        pos = line.find("</KW>");
                        line.erase(pos,5);

			string keyWord = line;
			string fullDes = newRoom->getFullDesc();
			string color;
			getline(roomFile,color);

			pos = color.find("<COL>");
			color.erase(pos,5);
			pos = color.find("</COL>");
			color.erase(pos,6);
			

			/*Tranlate the color from file into an actual color code*/
			string trueColor;
			if(color == "RESET")
				trueColor = RESET;
			else if(color == "BLACK")
				trueColor = BLACK;
			else if(color == "RED")
				trueColor = RED;
			else if(color == "GREEN")
				trueColor = GREEN;
			else if(color == "YELLOW")
				trueColor = YELLOW;
			else if(color == "BLUE")
				trueColor = BLUE;
			else if(color == "MAGENTA")
				trueColor = MAGENTA;
			else if(color == "CYAN")
				trueColor = CYAN;
			else if(color == "WHITE")
				trueColor = WHITE;
			else if(color == "BOLDBLACK")
				trueColor = BOLDBLACK;
			else if(color == "BOLDRED")
				trueColor = BOLDRED;
			else if(color == "BOLDGREEN")
				trueColor = BOLDGREEN;
			else if(color == "BOLDYELLOW")
				trueColor = BOLDYELLOW;
			else if(color == "BOLDBLUE")
				trueColor = BOLDBLUE;
			else if(color == "BOLDMAGENTA")
				trueColor = BOLDMAGENTA;
			else if(color == "BOLDCYAN")
				trueColor = BOLDCYAN;
			else if(color == "BOLDWHITE")
				trueColor = BOLDWHITE;
			else
				trueColor = RESET;
			

			//Find position of keyWord in fullDescription
			pos = fullDes.find(keyWord);
			//Insert the Color Choice at Description
			fullDes.insert(pos,trueColor);
			//Find position of keyWord again, so that we can reset color
			pos = fullDes.find(keyWord);
			fullDes.insert(pos+keyWord.length(),RESET);

			//Replace the original fullDescription
			newRoom->setFD(fullDes);

	

		}


            }//END of WHILE loop

		roomFile.close();
            }//END checking if file is open

else cout << "Unable to open Room Data File:" << fileNames.at(i) << endl;

            //add new room to roomVec
            if(!adj)
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


    mkdir(folderName.c_str(), 0777);

    vector<room*> theRooms = saveGame.getRooms();

    //Take each room in the current gameState and create a *.roomdat file
    for(int i = 0; i < (int)theRooms.size(); ++i){

	//Remove Spaces from Roomname
	string roomName = theRooms.at(i)->getName();
	roomName.erase(remove(roomName.begin(), roomName.end(), ' '), roomName.end());
        //Lets build our filePath!
        string filePath = folderName + "/" + roomName + ".roomdat";

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
            roomFile << "<C>" << adjacent.at(k)->getName() << "</C>" << endl;
        }

	//Check if room has been visited
	if(theRooms.at(i)->getVisited()){
	    roomFile << "<V>" << endl;
	}

        roomFile.close();

    }

    //After that is saved, we will save player information
    //Get Player 1 information
    player*  thePlayer = saveGame.getPlayer1();
    string playerPath = folderName + "/player.playerdat";
    ofstream playerFile(playerPath.c_str());
    playerFile << "<L>" << thePlayer->getLocation()->getName() << "</L>" << endl;

    vector<string> inventory = thePlayer->getInventory();

   for(int i = 0; i < (int)inventory.size(); ++i){
	playerFile << "<I>" << inventory.at(i) << "</I>" << endl;
   }



}

/******************************************************************************
** Function: loadGame()
** Description: Loads game state from existing save folder
** Parameters: name of save folder
*******************************************************************************/
void dataIO::loadGame(string folderName,game* newGame){

    //Here is where we will create a new Gamesate, first pulling the room data
    
    vector<room*> loadedRooms = roomIO(folderName.c_str());
    newGame->setRooms(loadedRooms);
    vector<string> fileNames;
    player* player1 = new player();
    //Need to set the player stuff
    //first we need to open the directory that our Player data files are in.

    dir = opendir(folderName.c_str());
    if(!dir){
      cout << "Directory Not Found, Error\n" << endl;
    }

	//read all file names in the given directory
     while((entry = readdir(dir)) != NULL){
      if(entry->d_name[0] != '.'){
         string name = string(entry->d_name);
          fileNames.push_back(name);
      }
 
    }
     //After that, we go through all of the vector, and process any with file extension *.playerdat

      for(int i = 0; i < (int)fileNames.size(); ++i){

     	if((size_t)fileNames.at(i).find(".playerdat") != std::string::npos){

		//build file name
		string theFile = folderName + "/" + fileNames.at(i);

		ifstream playerFile(theFile.c_str());

		if(playerFile.is_open()){

			string line;
			while(getline(playerFile,line)){
			size_t pos;

			//Finding location and setting it
			if(line.find("<L>") != std::string::npos){
			
				pos = line.find("<L>");
				line.erase(pos,3);
				pos = line.find("</L>");
				line.erase(pos,4);
			
				room* currentRoom;
				//check the room vector for the room
				for(int k = 0; k < (int)loadedRooms.size(); ++k){
					
					if(loadedRooms.at(k)->getName().compare(line) == 0){
						
						currentRoom = loadedRooms.at(k);
						break;
					}
				}

				if(currentRoom == NULL){
					cout << "Player's Room not Found" << endl;
				}

				else{
			
					player1->setLocation(currentRoom);}
			}

				if(line.find("<I>") != std::string::npos){
					pos = line.find("<I>");
					line.erase(pos,3);
					pos = line.find("</I>");
					line.erase(pos,4);
					player1->addToInventory(line);
				}
			}
		}
	}
     }
    newGame->setPlayers(player1);

/*    cout << newGame->getPlayer1()->getLocation()->getName() << endl;

    for(int j = 0; j < (int)newGame->getPlayer1()->getInventory().size(); ++j){
	cout << newGame->getPlayer1()->getInventory().at(j) << endl;
	}*/


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
