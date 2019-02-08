/***********************
 * 
 * Last Modified: 07 Feb 2019
 * Description: 
 * 
 **********************/

#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef PARSER_HPP
#define PARSER_HPP
 
	void dictMapInit();
	bool checkAlpha(string input);
	bool checkTerm(string str);
	vector<string> parseString();
	
#endif