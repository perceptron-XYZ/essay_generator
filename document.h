/*
 * Document.h
 *
 *  Created on: 2014-03-05
 *      Author: Ryan
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include "stopword.h"
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
class document{
public:
    document();
    document(string fileAddress);
    document(int indexSize);
    string getName() const;
    string getContent() const;
    void setContent(const string& newContent);
    vector<int> getPos() const;
    void setPos(const vector<int>& otherPos);
    vector<double> getIndex()const;
    void setIndex(const vector<double>& otherPos);
    double getSimilarity() const;
    void findIndex(const set<string>& allwords,int numDocs,vector<int>& singleCount,const vector<int>& allCount);
    void findSimToQuery(const document& query);
private:
    string name;
	string content;
	vector<double> index;
	vector<int> pos;
	double similarity;
    double product(const document& doc1) const;
    double magnitude() const;
};

void toLowerCase(string& word);
void removePunct(string& word);
void findAllIndices(const set<string>& allwords, vector<document>& sentences);




#endif /* DOCUMENT_H_ */
