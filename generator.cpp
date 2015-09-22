//============================================================================
// Name        : COMP345_A2_ver3.cpp
// Author      : XingyuZhou&JianLiu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "document.h"
#include "stopword.h"
#include "ranker.h"
#include "sentencesplitter.h"
#include "essayomat.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
using namespace std;

int main() {
	 cout<<"Welcome to use Essay Generator BETA edition."<<endl;
	      string essayQuestion;
	      string fileAddress;
	      int assignmentNo,selection;
	      cout<<"Please select assignment NO (1 or 2):"<<endl;
	      cin>>assignmentNo;
	      if(assignmentNo==1){
	    	  string filecollection = "a1docs\\fileList.txt";
			  ifstream ifs(filecollection.c_str());
			  string address;
			  stopword s;
			  set<string> allwords = s.readAll(filecollection.c_str(),false);
			  int k=1;
			  vector<document> documents;
			  while(getline(ifs,address)){
                 document d(address);
                 documents.push_back(d);
			  }
			  size_t numDocs = documents.size();
              cin.ignore();
              string query;
              int n;
              cout<<"What are you searching? To quit enter \'\\quit\':";
              getline(cin,query);
              	// keep asking for query until the user types in \quit.
              while(query!="\\quit"){
              	  cout<<"Enter the number of files you want to display: ";
              	  cin >> n;
              	  document q;
              	  q.setContent(query);
              	  if(documents.size()==numDocs+1)
              		  documents[numDocs]=q;
              	  else
              		  documents.push_back(q);
              	  findAllIndices(allwords,documents);
              	//find the similarities for all files with the query.
              	for(vector<document>::size_type i=0;i!=documents.size()-1;++i)
              		documents[i].findSimToQuery(documents[documents.size()-1]);
                cin.ignore();
              	ranker r;
                r.rank(documents);
              	r.showresults(documents,n);
                  // ask for next query
              	cout<<"What are you searching again? Hit \'\\quit\' to end search :";
              	getline(cin,query);
              	}
	      }
	      else if(assignmentNo==2){
			  cout<<"Please select the topic:"<<endl;
			  cout<<"Press 1 for Question 1" <<"\n"<<"Press 2 for Question 2 "<<"\n"<<"Press 3 for Question 3"<<"\n";
			  cin>>selection;
			  switch(selection){
			  case 1: essayQuestion = "q1.txt";
					  fileAddress = "q1list.txt";
					  break;
			  case 2: essayQuestion = "q2.txt";
					  fileAddress = "q2list.txt";
					  break;
			  case 3: essayQuestion = "q3.txt";
					fileAddress = "q3list.txt";
					  break;
			  }

			stopword s;
			set<string> allwords = s.readAll(fileAddress.c_str(),true);
			ifstream ifs(essayQuestion.c_str());
			string line,question;
			while(getline(ifs,line))
				question +=line;
			// declare and create the mini-document for essay question
			document q;
			q.setContent(question);
			// split all the articles into sentences
			sentencesplitter splitter;
			vector<document> sentences = splitter.split(fileAddress.c_str());
			// push the query document into the vector, so that all of them could be indexed together
			sentences.push_back(q);
		// index all the sentences
			findAllIndices(allwords,sentences);
		 // calculate the sims with respect to the query which is the last element of the vector
		   for(vector<document>::size_type i=0;i!=sentences.size()-1;++i)
			   sentences[i].findSimToQuery(sentences[sentences.size()-1]);

		  // generate essay.
		   essayomat generator;
		   generator.generateEssay(sentences,500);
	      }
    cout<<"Thanks for using Xingyu & Jian's File Index System. Bye! :)";
	return 0;
}
