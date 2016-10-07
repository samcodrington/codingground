#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "fileHandler.h"
#include "MyExceptions.h"
using namespace std;

// Turns filename.txt into a long vector of a string of insults
// Each line is seperated into it's own string
vector<string> fileHandler::getFile(string filename)
{
	ifstream file;
	file.open(filename);
	if (file.fail()) {
		FileException e= FileException("Unable to Open File");
		throw& e;
	}
	cout << "File opened successfully" << endl;
	vector<string> insults;
	string insult;
	while (getline(file, insult))
		insults.push_back(insult);
	file.close();
	return insults;

}

// This method returns a string[3] array with the insults passed with insultLIne
// sorted into seperate strings, with string[0] representing the first insult word
vector<string> fileHandler::addLine(string s)
{
	vector<string> threeInsults;
	istringstream iss(s);
	do {
		string word;
		iss >> word;
		threeInsults.push_back(word);
	} while (iss);
	threeInsults.pop_back(); //delete '\n' character
	if (threeInsults.size() != 3) {
		throw new NumInsultsOutOfBounds("Wrong number of Insults in Line!!");
	}
	return threeInsults;
}

void fileHandler::makeFile(string filename, vector <string> lines)
{
	ofstream ofs(filename, ofstream::out);
	if (ofs.fail())
		throw new FileException("Failed to create file"+filename);
	for (string s : lines)
		ofs << s << endl;
	ofs.close();
}
