/*******************************************************************************
** Program: parser.hpp
** Description: header file for natural language parser
*******************************************************************************/

#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef PARSER_HPP
#define PARSER_HPP
 
	void dictMapInit();
	bool checkAlpha(string input);
	bool checkTerm(string str);
	vector<string> parseString(string input);
	
#endif