#include "WordLadder.h"

#include <iostream>
#include <fstream>


#include <stack>
#include <queue>
#include <algorithm>
using std::queue;
using std::list;

using namespace std;

WordLadder::WordLadder(const string& filename) {
ifstream inFS; 
inFS.open(filename); // opens filename
  if (!inFS.is_open()) { // if file doesn't open the program stops
    cout << "Error opening file." << endl; 
    return;
  }

  string dictReader; 
  while (inFS >> dictReader) { // while dictReader gets an string the loop continues 
  if (dictReader.size() == 5) { // if the strings size is 5 then the word is pushed into dict which is a list
    dict.push_back(dictReader);
  }
  else{ // if the string is not 5 letters long then the programs stops working
    cout << "Error with word count" << endl;
    return;
  }
}
inFS.close(); 
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  ofstream outFS;
  outFS.open(outputFile);  // output file opens
  if(!outFS.is_open()){ // if file doesn't open the program stops
    cout << "Error Opening File" << endl;
    return;
  }
  queue<stack<string>> ladder; // queue named ladder that holds string stacks 
  stack<string> frontStack; // frontstack is the name of a string stack
  frontStack.push(start); // start word is pushed into frontStack 
  ladder.push(frontStack);  // front stack is pushed into ladder
 
while (!ladder.empty()) {
  stack<string>CopyStack = ladder.front(); // keeps a copy of the the ladders front stack as it will be deleted
  ladder.pop(); // deletes the front of the ladder so incase it holds the target word, the while loop will break
  string currWord = CopyStack.top(); // the first word of the stack 
  dict.remove(currWord); // Removes the current Word thats being checked so its not checked again
  if(currWord == end){ // checks if the current word is the equal to the target word
    stack<string> OrderedOutStack; // to output the stack in the right order
    while(!CopyStack.empty()){ 
      OrderedOutStack.push(CopyStack.top());// CopyStack words are being added to the OrderedOutstack in the correct order
      CopyStack.pop(); 
    }
    while(!OrderedOutStack.empty()){
      outFS << OrderedOutStack.top() << endl; // outputs the words of orderedOutStack into the file provided 
      OrderedOutStack.pop(); // deletes all the word in the stack
    }
    return; // stops the program as all the words have been found and reached the target word
  }
// if the current word is not the target word
for(unsigned int i = 0; i< dict.size(); i++){ //  loop to check every word in dict list 
  string CurrDictWord = dict.front(); 
  dict.pop_front();
  int counter = 0;
  for(int j = 0; j<5; j++){//checks if the current word has 4 matching letters 
    if(currWord.at(j) != CurrDictWord.at(j)){
      counter++;
    }
  }
  if(counter == 1){ // if there is exactly 4 matching letters
    stack<string>newStack = CopyStack; // a newStack is created to update the CopyStack 
    newStack.push(CurrDictWord); // the current Word is pushed into the newStack as it has matching letters and therefore it is now the updated copyStack
    ladder.push(newStack); // newStack is now pushed into the ladder as the first stack and the while loop continues again
  }
  else{ //if the current dictionary word is not matching then it is pushed back into the list as its can a matching word later on
    dict.push_back(CurrDictWord);
    }
  }
}
// outputs to the file if there are not enough or the right words to get from the start word to the target word
  outFS << "No Word Ladder Found." << endl;
  outFS.close();
  }

