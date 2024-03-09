/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "keywordSearcher.h"
#include "adts/stlMaxPriorityQueue.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

KeywordSearcher::KeywordSearcher() {
    this->corpus = new HashTable<string, HashTable<int, int>*>();
}

KeywordSearcher::~KeywordSearcher() {
    // contains all words in corpus
    vector<string> allWords = this->corpus->getKeys();

    // deletes each LinearDictionary stored at specified key
    for (int i = 0; i < allWords.size(); i++) {
        string wordToDelete = allWords[i];
        delete this->corpus->get(wordToDelete);
    }

    // deletes LinearDicitonary containing corpus hash table
    delete this->corpus;
}

void KeywordSearcher::loadWords(string filename) {
    ifstream myFile; // file being read
    string word;     // word currently being read in from myFile
    int pageNum;     // keeps page count

    // throws error if unable to open file
    myFile.open(filename);
    if (!myFile.is_open()) {
        throw runtime_error("file " + filename + " failed to open");
    }

    // reads in first word of file
    myFile >> word;

    // goes through file word by word while not trying to read past the end of the file
    while (!myFile.eof()) {
        // streams page number into pageNum when page indicator is read in
        if (word == "$$@@$$PAGE:") {
            myFile >> pageNum;
        }

        // inserts new hash table keyed on word into corpus if word does not
        // already exist in hash table
        if (!this->corpus->contains(word)) {
            // hash table keyed on the page number storing occurences 
            HashTable<int, int>* txt = new HashTable<int, int>();

            // initializes that word occurs on specified page once
            txt->insert(pageNum, 1);

            // inserts hash table keyed on specified word
            this->corpus->insert(word, txt);
        }
        // updates existing hash table if word already exists as key in corpus
        else {
            // increments occurences if word already appears on page
            if (this->corpus->get(word)->contains(pageNum)) {
                int temp = this->corpus->get(word)->get(pageNum);
                temp += 1;
                this->corpus->get(word)->update(pageNum, temp);
            }
            // initailizes occurence count to 1 when word appears on new page
            else {
                this->corpus->get(word)->insert(pageNum, 1);
            }
        }

        // reads in next word of file
        myFile >> word;
    }
}

vector<pair<int, int>> KeywordSearcher::search(string word) {
    // stores key-value pair containing page number and occurences
    vector<pair<int, int>> result;  

    // returns empty vector if word not found in corpus
    if (!this->corpus->contains(word)) {
        return result;
    }
    
    // saves number of pages word appears on
    int numPages = this->corpus->get(word)->getSize();  

    // contains all page number word appears on
    vector<int> pageNumbers = this->corpus->get(word)->getKeys();

    // stores frequency word appears on any one page
    vector<int> numFrequency; 

    // stores key-value pairs to be read into max priority queue
    vector<pair<int, int>> contents;   

    // populates contents with key-value pairs
    for (int i = 0; i < numPages; i++) {
        // gets frequency word appears on specified page
        numFrequency.push_back(this->corpus->get(word)->get(pageNumbers[i]));

        // creates key-value pair keyed on frequency storing page number 
        pair<int, int> temp;
        temp.first = numFrequency[i];
        temp.second = pageNumbers[i];

        // inserts pair into contents
        contents.push_back(temp);
    }
   
    // reads contents into a max prioritiy queue 
    STLMaxPriorityQueue<int,int> maxQ (contents);

    
    while (result.size() < 10 && numPages > 0) {
        // gets page number with highest occurences 
        int priority = maxQ.peekPriority();
        int value = maxQ.remove();

        // creates key-value pair keyed on page number storing frequency
        pair<int, int> tempResult;
        tempResult.first = value;
        tempResult.second = priority;

        // saves pair into result
        result.push_back(tempResult);

        // ensures while loop breaks if word appears on less than 10 pages
        numPages--;
    }

    return result;
}
