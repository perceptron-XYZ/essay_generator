/*
 * essayomat.h
 *
 *  Created on: 2014-02-17
 *      Author: Ryan
 */

#ifndef ESSAYOMAT_H_
#define ESSAYOMAT_H_
#include "document.h"
#include "ranker.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

class essayomat{
public:
	essayomat();
	void generateEssay(vector<document>& sentences,const int& length);

private:
    int countword(const string& sentence);
    const static string ESSAY;


};
bool posComparator(const document& v1,const document& v2);




#endif /* ESSAYOMAT_H_ */
