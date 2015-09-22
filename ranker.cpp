/*
 * ranker.cpp
 *
 *  Created on: 2014-02-22
 *      Author: Ryan
 */

#include "ranker.h"
#include "document.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;
bool pairCompare(const document& firstElem, const document& secondElem) {
        return firstElem.getSimilarity() > secondElem.getSimilarity();

      }

void ranker::rank(vector<document>& v1){
      	sort(v1.begin(),v1.end()-1,pairCompare);
      }

void ranker::showresults(const vector<document>& v1,int n){
	int counter = 0;
	cout << "The top "<<n<<" files that match your query are :" <<endl;
	for( vector<document>::const_iterator it = v1.begin(); it !=v1.end()-1; ++it )
	{   if(counter >= n)
		   return;
	   else{
		   cout << "file name: "<<it->getName()<<" with a score of : " << it->getSimilarity() <<endl;
		   counter++;
		    }
		}
}


