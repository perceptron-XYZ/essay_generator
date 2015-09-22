/*
 * stopword.h
 *
 *  Created on: 2014-02-07
 *      Author: Ryan
 */

#ifndef STOPWORD_H_
#define STOPWORD_H_

#include "document.h"
#include <string>
#include <set>
using namespace std;

class stopword{


public:
stopword();
set<string> readAll(const string& fileaddress,bool stop);

private:
bool isStopword(const string& word);
set<string> stopwords;
static const string stopwordsFile;
void toLowercase(string& word);
};

#endif /* STOPWORD_H_ */
