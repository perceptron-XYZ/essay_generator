/*
 * sentencesplitter.h
 *
 *  Created on: 2014-02-17
 *      Author: Ryan
 */

#ifndef SENTENCESPLITTER_H_
#define SENTENCESPLITTER_H_

#include "document.h"
#include <vector>
#include <string>
using namespace std;
class sentencesplitter{
public:
	sentencesplitter(){};
	vector<document>& split(const string& file);



private:
	bool endwith(char symbol);
	void adjustword(string& word);


};

#endif /* SENTENCESPLITTER_H_ */
