/*
 * essayomat.cpp
 *
 *  Created on: 2014-02-17
 *      Author: Ryan
 */

#include "essayomat.h"
#include "stopword.h"
#include "ranker.h"
#include "sentencesplitter.h"

#include<vector>
#include<utility>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

const string essayomat::ESSAY = "essay.txt";
essayomat::essayomat(){};
bool posComparator(const document& v1,const document& v2){
	       if(v1.getPos()[0]<v2.getPos()[0])
	    	   return true;
	       else if(v1.getPos()[0]==v2.getPos()[0])
	    	   return v1.getPos()[1]<v2.getPos()[1];
	       else return false;
}
int essayomat::countword(const string& sentence){
	  istringstream wordstream(sentence);
	   int wordCount=0;
	   string word;
	   while(wordstream>>word)
		   ++wordCount;
	   return wordCount;
}
void essayomat::generateEssay(vector<document>& docs,const int& length){

       int num=0;
       ranker r;
       r.rank(docs);
       vector<document> selected;
       string sentence;
       for(vector<document>::const_iterator it=docs.begin();it!=docs.end()-1;++it){
    	                 sentence=it->getContent();
                         num += countword(sentence);
                         if(num<=length)
                      	   selected.push_back(*it);
                         else
                        	 break;
              }
       sort(selected.begin(),selected.end(),posComparator);
       ofstream output(ESSAY.c_str());
       string s1("File "),s2(" Sentence "),s3(": ");
       for(vector<document>::const_iterator it=selected.begin();it!=selected.end();++it){
    	      output<<s1<<it->getPos()[0]<<s2
    	    		  <<it->getPos()[1]<<s3<<it->getContent()<<endl;
              }
       cout<<"ESSAY GENERATION COMPLETE!!"<<endl<<"It has been written to file:" <<ESSAY;
}




