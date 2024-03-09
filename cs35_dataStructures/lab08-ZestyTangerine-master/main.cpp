/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <vector>

#include "keywordSearcher.h"

using namespace std;

int main(int argc, char** argv) {
    // ensures user only passes in one argument
    if (argc != 2) {
      throw runtime_error("Please enter valid command line arguments!");
    }
    else {
      string filename = argv[1];
      KeywordSearcher searcher;

      // generates hash table containing all words and occurences
      searcher.loadWords(filename);
      cout << "File loaded" << endl;
      cout << endl;

      // asks user to input a word to search for using searcher
      string wordToSearch;
      while (wordToSearch != "!"){
        cout << "Please enter a search word or '!' to quit: ";
        cin >> wordToSearch;
        
        // generates hash table keyed on page numbers and storing occurences
        vector<pair<int, int>> results = searcher.search(wordToSearch);
        
        // prints out top ten pages within doument containing inputted keyword
        // the most times if word exists and user is not quitting
        if (results.size() == 0 && wordToSearch != "!") {
          cout << "The word ";
          cout << wordToSearch;
          cout << " does not appear in the file." << endl;
          cout << endl;
        } 
        else if (wordToSearch != "!") {
          cout << "The word ";
          cout << wordToSearch;
          cout << " appears in the file..." << endl;
          
          // iterates over length of results and prints out statement with
          // the page number the word appears on and number of occurences
          for (int i = 0; i < results.size(); i++) {
            cout << "    on page ";
            cout << results[i].first;
            cout << " (";
            cout << results[i].second;
            cout << " occurences)" << endl;
          }
          cout << endl;
        }
        
      }

      cout << endl;
      cout << "Goodbye!" << endl;
    }
    return 0;
}
