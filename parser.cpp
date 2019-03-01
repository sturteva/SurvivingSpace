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
			return false;
		}
	}
	
	return true;
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
	bool bagFlag = false;
	bool lookFlag = false;
	bool formatFlag = false;

	
	//run a while loop while foundFlag is false
	do
	{
		//empty everything out
		cin.clear();
		input = "";
		//make sure the command vector is empty
		while (!command.empty())
		{
			command.pop_back();
		}
		
		cout << endl << ">> ";
		getline(cin, input);
		
		/***************
		 *Debug Command
		 ***************/
		//cout << "DEBUG (raw input): " << input << endl;
	
		if (input != "" && input.at(input.length() - 1) == '.')
		{
			input = input.substr(0, input.length() - 1);
		}
		if (checkAlpha(input))
		{
			formatFlag = true;
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
		else
		{
			formatFlag = false;
		}
		
		if (formatFlag)
		{
			/***************
			*Debug Command
			***************/
			//cout << "DEBUG (adjusted input): " << input << endl;
	
			//check to see if dictionary terms are in the string, starting with verbs
			for (std::map<string,string>::iterator itr = verbDict.begin(); itr != verbDict.end();)
			{
				string tempString = itr->first;
			
				/***************
				*Debug Command
				***************/
				//cout << "DEBUG (verb): " << itr->first << " | " << itr->second << endl;
			
				size_t found = input.find(tempString);
			
				//check for special commands that function differently
				if (found != npos && (tempString == "inventory" || tempString == "bag") && !bagFlag)
				{
					bagFlag = true;
					++itr;
					//cout << "DEBUG (bagFlag): set to true." << endl;
				}
				else if (found != npos && (tempString == "look"))
				{
					lookFlag = true;
					++itr;
					//cout << "DEBUG (lookFlag): set to true." << endl;
				}
				//if we didn't find either of those, push it back
				else if (found != npos)
				{
					//push back the value for the found key
					//cout << "DEBUG (Found Verb): " << itr->second << endl;
					command.push_back(itr->second);
					//set iterator to the end
					itr = verbDict.end();
					foundFlag = true;
				}
				else
				{
					++itr;
				}
			}
		
			if (!foundFlag && bagFlag)
			{
				//if we have this combination of flags, then the verb is "inventory", so push it back
				command.push_back("inventory");
				foundFlag = true;
				bagFlag = false;
			}
		
			if (!foundFlag && lookFlag)
			{
				//if we have this combination of flags, then the verb is "look", so push it back
				command.push_back("look");
				foundFlag = true;
				lookFlag = false;
			}
	
			//if foundFlag is still false at this point or if the command is "go", check for a direction or a room; return an error if not found
			if (!foundFlag || (foundFlag && command[0] == "go"))
			{
				for (std::map<string,string>::iterator itr = roomDict.begin(); itr != roomDict.end();)
				{
					string tempString = itr->first;
				
					/***************
					*Debug Command
					***************/
					//cout << "DEBUG (moving): " << itr->first << " | " << itr->second << endl;
				
					size_t found = input.find(tempString);
			
					if (found != npos)
					{
						//push back "go" if not already done and the value for the found key
						if (command.size() == 0)
						{
							command.push_back("go");
						}
						command.push_back(itr->second);
						//set iterator to the end
						itr = roomDict.end();
						foundFlag = true;
					}
					else
					{
						++itr;
					}
				}
				if (command.size() == 0)
				{
					foundFlag = false;
					cout << "The provided verb was not understood." << endl;
				}
				else if (command.size() != 2)
				{
					command.pop_back();
					foundFlag = false;
					cout << "The destination was invalid." << endl;
				}
			}
			
			//code for "look at" goes here
			
			
			
			//code for "use" goes here
			
		
			//if foundFlag is true at this point, check for dictionary terms
	
			if (foundFlag && command[0] != "go")
			{
				if (command[0] != "look" && command[0] != "exit" && command[0] != "help" && command[0] != "inventory" && command[0] != "hint" && command[0] != "savegame" && command[0] != "loadgame")
				{
					for (std::map<string,string>::iterator itr = nounDict.begin(); itr != nounDict.end();)
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
							//set iterator to the end
							itr = nounDict.end();
							foundFlag = true;
						}
						else
						{
							++itr;
						}
					}
					if (command.size() != 2)
					{
						command.pop_back();
						foundFlag = false;
						cout << "The provided noun was not understood." << endl;
					}
				}
			}
		}
		
	} while (!foundFlag);
	
	/***************
	*Debug Command
	***************/
	/*cout << "DEBUG (pre-send): " << command[0];
	if (command.size() > 1)
	{
		cout << " " << command[1];
	}
	cout << endl;*/
	
	
	//culling the for loops into one callable function using the parameters would be better and more efficient code
	
	return command;
}

