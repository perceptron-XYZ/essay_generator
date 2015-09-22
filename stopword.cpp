/*
 * stopword.cpp
 *
 *  Created on: 2014-02-07
 *      Author: Ryan
 */
#include "stopword.h"
#include "document.h"
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

const string stopword::stopwordsFile = "stopwords.txt";

stopword::stopword(){
	string word;
    ifstream ifs(stopwordsFile.c_str());
    while(ifs>>word)
    	stopwords.insert(word);
    ifs.close();
}
bool stopword::isStopword(const string& word){
   return stopwords.count(word)!=0;
}
/**
 *  Put the distinct non-stopword words in all files into a set.
 */
void  stopword::toLowercase(string& word){
	int length = word.size();
   	for (int i = 0; i < length; ++i)
   	    word[i] = tolower(word[i]);

}
set<string> stopword::readAll(const string& fileaddress,bool stop){
	string word,line;
	vector<string> files;
	ifstream filestream(fileaddress.c_str());
	while(getline(filestream,line)){
		cout<<line<<endl;
		files.push_back(line);}

	set<string> allwords;
    for(vector<string>::size_type i=0;i!=files.size();++i){
		ifstream ifs2(files[i].c_str());
		while(ifs2>>word){
		toLowercase(word);
		removePunct(word);
		if(word.size()!=0){
		   if(stop){
			   if(!isStopword(word))
			   allwords.insert(word);
		       }
		   else
			   allwords.insert(word);
		     }
		   }
         }
	   return allwords;
      }





