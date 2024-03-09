/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

int main() {
    // TODO: write any tests you want here; this is your sandbox

    List<pair<int, string>>* list = loadMovie("test_data/scene2.asciimation");
    for (int i = 0; i < list -> getSize(); i++) {
      cout << list -> getFirst().first << endl; 
      cout << list -> getFirst().second << endl;
      list -> removeFirst();
    }

    return 0;
}
