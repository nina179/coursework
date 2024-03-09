/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

int main(int argc, char** argv) {
    string first = argv[1];
    if (argc == 2) {
      //if only two arguments then playMovie normally
      string file = first;
      List<pair<int, string>>* x = loadMovie(file);
      playMovie(x);
    }
    else if (argc == 3 && first == "--reverse") {
      //if three arguments and middle argument is --reverse, play movie reversed
      string file = argv[2];
      //load how movie would be played normally
      List<pair<int, string>>* x = loadMovie(file);
      LinkedList<pair<int, string>>* reversed = new LinkedList<pair<int, string>>;
      int size = x->getSize();
      for (int i = 0; i < size; i++) {
        //continuously take the first element and place it in the beginning of the reversed list
        //this reverses the overall order of the frames
        pair<int, string> temp = x->getFirst();
        reversed->insertFirst(temp);
        x -> removeFirst();
      }
      delete x;
      playMovie(reversed);
    }
    else {
      //if an invalid argument, return a message saying so
      cout << "Invalid number of arguments" << endl;
    }
    return 0;
}
