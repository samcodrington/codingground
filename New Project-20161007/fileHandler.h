#pragma once
#include <vector>
#include <string>
using namespace std;
//Class of methods for use in initialize method of InsultGenerator
class fileHandler
{
public:

	// This method returns a string vector (size=3)
	// the insults passed with insultLIne sorted into seperate strings,
	// (ie. string[0] representing the first insult word, etc.)
	static vector<string> addLine(string);
	// Turns filename.txt into a long string of insults, with each line seperated by \n
	static vector<string> getFile(string);
	static void makeFile(string,vector<string>);
};

