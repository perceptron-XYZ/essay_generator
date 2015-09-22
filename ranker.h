/*
 * ranker.h
 *
 *  Created on: 2014-02-22
 *      Author: Ryan
 */

#ifndef RANKER_H_
#define RANKER_H_
#include "document.h"
#include <vector>
#include <string>
using namespace std;

class ranker{
    public:
	void rank(vector<document>& documents);
	void showresults(const vector<document>& v1,int n);
  //  private:

};
bool pairCompare(const document& first, const document& second);

#endif /* RANKER_H_ */
