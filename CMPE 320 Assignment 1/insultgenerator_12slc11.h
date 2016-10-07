#pragma once
#include <vector>
#include <string>

#include "MyExceptions.h"
using namespace std;

//Class for InsultGenerator Class with methods to intiialise
class InsultGenerator {
public:
	void initialize();		//Loads source phrases from InsultsSource.txt
	string talkToMe();		//Returns single randomly generated insult with error conditions for improper attributes
	vector<string> generate(int);	//Generates number of unique insults
	void generateAndSave(string,int); //Saves generated insults to text file, uses generate(int)

protected:
	//genRandNums creates a vector of i random integers where every number only appears once
	vector <int> genRandNums(int); 
	bool randGood(vector<int>, int);	//Checks that integer has not been repeated in the vector
	void increment(int, int&, int&, int&); //Increments three indices by references according to array of size i;
	

private:
	void addToList(string,vector<string>&); //appends a string  to whichever list
	void setSize();	//

	vector <string> adj1, adj2, noun; //Insult component
	int size; //Contains size of adjective, noun lists
	string genInsult(int,int,int);
};

