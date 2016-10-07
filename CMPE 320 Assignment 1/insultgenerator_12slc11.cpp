#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include "insultgenerator_12slc11.h"
#include "fileHandler.h"
#include "MyExceptions.h"
using namespace std;

void InsultGenerator::initialize()
{
	vector<string> insults, insultWords;
	int i = 1;
	//Generate vector of 50 insult strings
	insults = fileHandler::getFile("InsultsSource.txt");

	//Divide each string into 3 strings of one word each
	for (string s : insults) {
		insultWords = fileHandler::addLine(s);
		addToList(insultWords[0],adj1);
		addToList(insultWords[1],adj2);
		addToList(insultWords[2],noun);
	}
	setSize();
}
void InsultGenerator::addToList(string s, vector<string>& list) {list.push_back(s);}

void InsultGenerator::setSize() {
	try {
		if ((adj1.size() == adj2.size()) && (noun.size() == adj2.size()))
			InsultGenerator::size = adj1.size();
		else
			throw new NumInsultsOutOfBounds("Word lists not same size");
	}
	catch (NumInsultsOutOfBounds &e) {
		cerr << "Stringsize mismatch!" << endl;
		cerr << "Adj1 has size: " << adj1.size() << endl;
		cerr << "Adj2 has size: " << adj2.size() << endl;
		cerr << "Noun has size: " << noun.size() << endl;
	}
	
}

string InsultGenerator::talkToMe()
{
	const int num (adj1.size());
	int rand1, rand2, rand3;
	if (num > 0) {
		srand(time(NULL));
		rand1 = rand() % num;
		rand2 = rand() % num;
		rand3 = rand() % num;
		string insult = genInsult(rand1,rand2,rand3);
		return insult;
	}
	else {
		cerr << "No List!!" << endl;
		return "Adjective List Empty";
	}
}

string InsultGenerator::genInsult(int i, int j, int k)
{
	string insult;
	try {
		if (i < size && j < size && k < size){
			insult = "Thou " + adj1[i] + " " + adj2[i] + " " + noun[k] + "!";
			return insult;
		}
		else
			throw new NumInsultsOutOfBounds("Invalid Insult due to Out of Bounds");
	}
	catch (NumInsultsOutOfBounds& e) {
		return "Invalid Insult due to Out of Bounds";
	}
}

void InsultGenerator::generateAndSave(string filename, int num)
{
	vector<string> insultList;
	try {
		insultList = generate(num);
	}
	catch(NumInsultsOutOfBounds& e) {throw e;}
	//sortLines(insultList);
	try {
		fileHandler::makeFile(filename, insultList);
	}
	catch (NumInsultsOutOfBounds& e) {throw e;}


}

vector<string> InsultGenerator::generate(int num)
{
	vector <string> insultList;

	//try {
	if (num < 1 || num>10000) {
		string s = "Tried to create ";
		s+= num;
		s+= " insults. Number is not between 0 and 10000";
		throw new NumInsultsOutOfBounds(s);
	}
		
	/*}
	catch (NumInsultsOutOfBounds e) {
		e.what();
		throw e;
	}//*/
	
	
	int i(1);
	while ((i*i*i) < num) { i++; }
	
	const vector <int> randoms(genRandNums(i));

	int a(0); int b(0); int c(0);
	int& aRef(a); int& bRef(b); int& cRef(c);
	int rand1, rand2, rand3;
	string insult;

	while (insultList.size() < num) {
		rand1 = randoms[a];
		rand2 = randoms[b];
		rand3 = randoms[c];

		insult = genInsult(rand1, rand2, rand3);
		insultList.push_back(insult);

		increment(i, aRef, bRef, cRef);
	}
	return insultList;
};



vector<int> InsultGenerator::genRandNums(int i)
{
	vector <int> randoms;
	srand(time(NULL));
	int randCandidate;
	for (int j = 0; j < i; j++) {
		randCandidate = rand() % size;
		if (randGood(randoms, randCandidate)) {
			randoms.push_back(randCandidate);
		}
		else j--;
	}
	return randoms;
}

bool InsultGenerator::randGood(vector<int> randoms, int candidate)
{
	for (int i = 0; i < randoms.size(); i++) {
		if (randoms[i] == candidate) return false;
	}
	return true;
}

void InsultGenerator::increment(int i, int& a, int& b, int& c)
{
	if (c < i - 1)
		c++;
	else if (c == i - 1) {
		c = 0;
		if (b < i - 1)
			b++;
		else if (b == i - 1) {
			b = 0; c = 0;
			if (a < i - 1)
				a++;
			else if (a == i - 1)
				return;
		}
	}
}


