/*
 * document.cpp
 *
 *  Created on: 2014-03-05
 *      Author: Ryan
 */

#include "document.h"
#include "stopword.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<cmath>
#include<map>
#include<ctype.h>
using namespace std;
document::document():similarity(0.0){
	pos.resize(2);
}
document::document(string fileAddress):similarity(0.0){
	 name = fileAddress;
	 ifstream ifs(fileAddress.c_str());
	 string line;
	 while(getline(ifs,line)){
		 content += line;
	 }
}
document::document(int indexSize):similarity(0.0){
	index.resize(indexSize);
}
string document::getName() const{
	return name;
}
string document::getContent() const{
	return content;
 }
void document::setContent(const string& newContent){
	content = newContent;
}
vector<int> document::getPos() const{
	return pos;
}
void document::setPos(const vector<int>& otherPos){
    for(vector<int>::size_type i=0;i!=otherPos.size();++i)
    	pos[i]=(otherPos[i]);

}
vector<double> document::getIndex() const{
	return index;
}
void document::setIndex(const vector<double>& otherIndex){
	index.resize(otherIndex.size());
	for(vector<double>::size_type i=0;i!=otherIndex.size();++i)
	    	index[i]=(otherIndex[i]);
}
double document::getSimilarity() const{
	return similarity;
}


void  toLowercase(string& word){
	int length = word.size();
   	for (int i = 0; i < length; ++i)
   	    word[i] = tolower(word[i]);
}
void  removePunct(string& word){
	for(unsigned int i=0,len=word.size();i<len;i++){
		            if((i==len-2)&&((word[i]=='\''&&word[i+1]=='s')||(word[i]=='s'&&word[i+1]=='\'')))
		            	break;
		            else if(!isalnum(word[i]))
		            	{
		            	word.erase(i--,1);
		            	len=word.size();
		            	}
		        }

}

void findAllIndices(const set<string>& allwords,vector<document>& sentences){
	         cout<<"scanning through all documents started...";
             vector<int> occ(allwords.size());
	         vector<vector<int> > fre(sentences.size());
	         for(vector<vector<int> >::size_type m=0;m!=fre.size();++m){
	        	 fre[m] = vector<int>(allwords.size());
	         }
	         int k=0;
	         double result;
	         string word,sentence;
	         for(set<string>::const_iterator i=allwords.begin();i!=allwords.end();++i){
	                	  for(vector<string>::size_type j=0;j!=sentences.size();++j){
	                		  sentence=sentences[j].getContent();
	                		  istringstream iss(sentence.c_str());
	                		  while(iss>>word){
	                			  toLowercase(word);
	                			  removePunct(word);
	                			  if(word==*i){
	                				  ++fre[j][k];       // j-th file, k-th word
	                			  }
	                		  }
	                	  }
	                	  ++k;
	                	  cout<<k<<"/"<<allwords.size()<<"finished."<<endl;
	                  }
	      cout<<"Preparing...."<<endl;
	      int temp=0;
	      vector<double> tempVec(allwords.size());
	      for(size_t z=0;z!=allwords.size();++z){
	         for(vector<vector<int> >::size_type m=0;m!=fre.size()-1;++m){
	         	         if(fre[m][z]>=1)
	        	             temp +=1;
	         	         }
	         occ[z] = temp;
	         temp=1;
	      }


          for(vector<string>::size_type i=0;i!=sentences.size();++i){
        	  for(size_t j=0;j!=allwords.size();++j){
        		  if(fre[i][j]==0)
        			  result=0;
        		  else
        			  result =(1+log(fre[i][j]))*log10((sentences.size()-1)/occ[j]);

        	  tempVec[j] = result;
        	  }
          sentences[i].setIndex(tempVec);
          }

}

double document::product(const document& doc) const{
	double sum=0;
	for(vector<double>::size_type i=0;i!=doc.getIndex().size();i++){
		sum+=index[i]*doc.getIndex()[i];
	}
	return sum;
}

double document::magnitude() const{
	double sum=0.0;
	for( vector<double>::size_type i=0;i!=index.size();i++){
			sum+=index[i]*index[i];
		}
	return sqrt(sum);
}

void document::findSimToQuery(const document& query) {
	if(magnitude()==0.0||query.magnitude()==0.0)
			similarity=0.0;
		else
			similarity= product(query)/(magnitude()*query.magnitude());
}













