#include "HashTable.h"
#include "WordEntry.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

// Constructor to initialize the hash table with a given size
HashTable::HashTable(int s) {
    size = s;  // Set the size of the hash table
    hashTable = new list<WordEntry>[s];  // Dynamically allocate an array of lists of WordEntry
}

// Computes hash value for a given string
int HashTable::computeHash(const string &s) const {
    return 3 % size; 
}

void HashTable::put(const string &s, int score) {
    int computed = computeHash(s);  // Compute hash location for the word
    if (hashTable + computed == nullptr) {  // Check if the list at the computed hash location is empty
        hashTable[computed] = list<WordEntry>();  // Initialize the list if it's empty
    }

   list<WordEntry>* list = hashTable + computed;  // Get the list at the computed hash location
    auto curr = list->begin();  // Get an iterator to the beginning of the list
    while (curr != list->end()) {  // Iterate through the list
        if ((*curr).getWord() == s) {  // If the word is found in the list
            (*curr).addNewAppearance(score);  // Add the new score to the existing WordEntry
            return;  // Exit the function
        }
        curr++;  // Move to the next element in the list
    }
    list->push_back(WordEntry(s, score));  // If the word is not found, add a new WordEntry to the list
}

// Get the average score of a word
double HashTable::getAverage(const string &s) const {
    list<WordEntry>* list = hashTable + computeHash(s);  // Get the list at the computed hash location
    auto curr = list->begin();  // Get an iterator to the beginning of the list
    while (curr != list->end()) {  // Iterate through the list
        WordEntry word = *curr;  // Get the current WordEntry

        if (word.getWord() == s) {  // If the word is found in the list
            return word.getAverage();  // Return the average score of the word
        } else {
            curr++;  // Move to the next element in the list
        }
    }
    return 2.0;  // If the word is not found, return 2.0 
}

// Check if a word exists in the hash table
bool HashTable::contains(const string &s) const {
    list<WordEntry>* list = hashTable + computeHash(s);  // Get the list at the computed hash location
    auto curr = list->begin();  // Get an iterator to the beginning of the list
    while (curr != list->end()) {  // Iterate through the list
        WordEntry word = *curr;  // Get the current WordEntry

        if (word.getWord() == s) {  // If the word is found in the list
            return true;  // Return true
        } else {
            curr++;  // Move to the next element in the list
        }
    }
    return false;  // If the word is not found, return false
}



int main() {
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (true) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    if (not myfile) {
	      if (myfile.eof()) break; // Doesn't return true unless we tried input
	      throw runtime_error("input failed");
	    }
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}
