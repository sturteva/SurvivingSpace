/*******************************************************************************
** Program: parser.cpp
** Description: Implementation file for natural language parser
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <map>
#include <typeinfo> //for debugging

using std::cin;
using std::cout;
using std::endl;
using std::getline;

using std::vector;
using std::string;
using std::map;
using std::pair;

using std::numeric_limits;
using std::streamsize;
using std::isalpha;
using std::isspace;
using std::tolower;

using std::ifstream;

auto npos = std::string::npos;


/*******************************************************************************
** Globals
** Naughty declaration of dictionary terms as global variables
*******************************************************************************/

map<string, string> verbDict;
map<string, string> nounDict;
map<string, string> roomDict;


/******************************************************************************
** Function: dictMapInit()
** Description: Read files in from the "dictionary" of terms that the game
**				understands and store them in a map for easy lookup and
**				conversion into terms the game can use.
** Parameters: None
** Returns: None
*******************************************************************************/
void dictMapInit()
{
	//declare variables
	string data = "";
	string key = "";
	ifstream inputFile;

	//open the verbs file; don't forget to close it later!
	inputFile.open("verbs.dat");

	//add terms from the file with while loop
	while (getline(inputFile, key, '|') && getline(inputFile, data))
	{
		//can't remember if need this or not; thinking not, but here just in case for now
		//myfile.ignore(numeric_limits<streamsize>::max(), '\n');
		verbDict.insert(pair<string, string>(key, data));
	}
	
	//closing the verb file here
	inputFile.close();
	
	
	//open the noun file; don't forget to close it later!
	inputFile.open("nouns.dat");
	
	//add terms from the file with while loop
	while (getline(inputFile, key, '|') && getline(inputFile, data))
	{
		nounDict.insert(pair<string, string>(key, data));
	}
	
	//close the noun file here
	inputFile.close();
	
	
	//open the rooms file; don't forget to close it later!
	inputFile.open("rooms.dat");
	
	//add terms from the file with while loop
	while (getline(inputFile, key, '|') && getline(inputFile, data))
	{
		roomDict.insert(pair<string, string>(key,data));
	}
	
	//close the noun file here
	inputFile.close();
	
}


/******************************************************************************
** Function: checkAlpha()
** Description: Checks to make sure that a user's string input contains only
** 				letters and spaces.
** Parameters: String to be checked
** Returns: bool if string contains only letters and numbers
*******************************************************************************/
bool checkAlpha(string input)
{
	int strLength = input.length();
	for (int pos = 0; pos < strLength; pos++)
	{
		if (!isalpha(input[pos]) && !isspace(input[pos]))
		{
			cout << "Invalid input. Commands should contain letters and spaces only, no punctuation." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}
	}
	
	return true;
}

/******************************************************************************
** Function: checkTerm()
** Description: Checks to see if a word provided by the user is in the
** 				dictionary of known terms. Returns the type of word (noun,
**				verb, other)and its accepted format to the calling function.
** Parameters: String to be checked
** Returns: bool if the term is in dictionary
*******************************************************************************/
bool checkTerm(string str)
{
	
	return false;
}


/******************************************************************************
** Function: parseString()
** Description: Parse the string into a command the game will recognize.
** Parameters: command to parse
** Returns: Vector of strings containing commands
*******************************************************************************/
vector<string> parseString()
{
	//declare variables
	vector<string> command;
	string input;
	bool foundFlag = false;
	
	
	//make sure the command vector is empty
	while (!command.empty())
	{
		command.pop_back();
	}
	
	//run a while loop while foundFlag is false
	do
	{
		cin.clear();
		cout << endl << ">> ";
		getline(cin, input);
		
		/***************
		 *Debug Command
		 ***************/
		cout << "DEBUG (raw input): " << input << endl;
	
		if (input != "" && input.at(input.length() - 1) == '.')
		{
			input = input.substr(0, input.length() - 1);
		}
		if (checkAlpha(input))
		{
			//change the command to all lowercase
			int strLength = input.length();
			for (int pos = 0; pos < strLength; pos++)
			{
				if (!isspace(input[pos]))
				{
					input[pos] = tolower(input[pos]);
				}
			}
		}
		
		/***************
		 *Debug Command
		 ***************/
		cout << "DEBUG (adjusted input): " << input << endl;
	
		//check to see if dictionary terms are in the string, starting with verbs
		for (std::map<string,string>::iterator itr = verbDict.begin(); itr != verbDict.end(); ++itr)
		{
			string tempString = itr->first;
			
			/***************
			*Debug Command
			***************/
			//cout << "DEBUG (verb): " << itr->first << " | " << itr->second << endl;
			
			size_t found = input.find(tempString);
			
			if (found != npos)
			{
				//push back the value for the found key
				command.push_back(itr->second);
				//set the itr to the end of the dict so that it will end the for loop
				itr = verbDict.end();
				foundFlag = true;
			}
		}
	
		//if foundFlag is still false at this point, check for a direction or a room; return an error if not found
		if (!foundFlag || (foundFlag && command[0] == "go"))
		{
			for (std::map<string,string>::iterator itr = roomDict.begin(); itr != roomDict.end(); ++itr)
			{
				string tempString = itr->first;
				
				/***************
				*Debug Command
				***************/
				//cout << "DEBUG (moving): " << itr->first << " | " << itr->second << endl;
				
				size_t found = input.find(tempString);
			
				if (found != npos)
				{
					//push back "go" and the value for the found key
					if (command.size() == 0)
					{
						command.push_back("go");
					}
					command.push_back(itr->second);
					//set the itr to the end of the dict so that it will end the for loop
					itr = roomDict.end();
					foundFlag = true;
				}
				else if (itr == roomDict.end() && !foundFlag)
				{
					cout << "No recognized verb, direction or room name was provided." << endl;
				}
			}
		}		
		
		//if foundFlag is true at this point, check for dictionary terms
	
		if (foundFlag && command[0] != "go")
		{
			if (command[0] != "look" && command[0] != "exit" && command[0] != "help")
			{
				for (std::map<string,string>::iterator itr = nounDict.begin(); itr != nounDict.end(); ++itr)
				{
					string tempString = itr->first;
				
					/***************
					*Debug Command
					***************/
					//cout << "DEBUG (not moving): " << itr->first << " | " << itr->second << endl;
				
					size_t found = input.find(tempString);
			
					if (found != npos)
					{
						//push back the value for the found key
						command.push_back(itr->second);
						//set the itr to the end of the dict so that it will end the for loop
						itr = nounDict.end();
						foundFlag = true;
					}
				}
			}
		}
		
	} while (!foundFlag);
	
	/***************
	*Debug Command
	***************/
	cout << "DEBUG (pre-send): " << command[0] << " " << command[1] << endl;
	
	
	//culling the for loops into one callable function using the parameters would be better and more efficient code
	
	return command;
}

