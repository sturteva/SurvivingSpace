/***********************
 * 
 * Last Modified: 07 Feb 2019
 * Description: 
 * 
 **********************/
 
 #include <iostream>
 #include <vector>
 #include <string>
 #include "parser.hpp"
 
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
	//declare variables
	vector<string> command;
	
	//initiate the dictionaries
	dictMapInit();
	
	cout << "Input command here:" << endl;
	
	command = parseString();
	
	cout << "Parsed Command: ";
	for (int count = 0; count < command.size(); count++)
	{
		cout << command[count] << " ";
	}
	cout << endl;
	
	return 0;
}