/*
 * sentencesplitter.cpp
 *
 *  Created on: 2014-02-17
 *      Author: Ryan
 */

#include "sentencesplitter.h"
#include "document.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;
void sentencesplitter::adjustword(string& word){

	for(unsigned int i=0,len=word.size();i<len;i++){
	             if(isspace(word[i])||(word[i]=='.')||(word[i]=='?')||(word[i]=='!'))
	            	 continue;
		         else if(!isalnum(word[i]))
			            	{
			            	word.erase(i--,1);
			            	len=word.size();
			            	}
	}
}
vector<document>& sentencesplitter::split(const string& file){
       string oneFile;
	   string word;
       string currentSentence;
       char endSymbol;
       document* sentence = new document();
       vector<document>* allSentences = new vector<document>;
       vector<int> tempPos;
       int fileNo=1,sentenceNo=1;
       ifstream ifs(file.c_str());
       while(getline(ifs,oneFile)){
    	   ifstream ifs2(oneFile.c_str());
    	   while(ifs2>>word){
    	   if(word.size()>0){
               adjustword(word);
    		   endSymbol = word[word.size()-1];
    		   currentSentence.append(word);
    		   currentSentence.append(" ");
    		   if(endwith(endSymbol)){
    			   tempPos.push_back(fileNo);
    			   tempPos.push_back(sentenceNo);
    			   sentence->setContent(currentSentence);
    			   sentence->setPos(tempPos);
    			   currentSentence.clear();
    			   allSentences->push_back(*sentence);
    			   tempPos.clear();
    			   ++sentenceNo;

    		   }
            }

         }
    	   ++fileNo;
    	   sentenceNo=1;
     }
      return *allSentences;
}


bool sentencesplitter::endwith(char symbol){

	return (symbol=='.')||(symbol=='?')||(symbol=='!');
}


