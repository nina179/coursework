/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;


List<pair<int, string>>* loadMovie(string filename) {
  //creates linked list of pairs that include the number of frames to display for and the image to display
  ifstream myFile;
  string data;
  string frames;
  string temp;

  int count = 1;
  LinkedList<pair<int, string>>* list = new LinkedList<pair<int, string>>;

  myFile.open(filename);

  if(!myFile.is_open()) {
    throw runtime_error("file " + filename + "failed to open ");
  }
  getline(myFile, frames);

  while (!myFile.eof()) {   
    //read until end of file, every 14 lines checking for frames, then next 13 lines creating the image 
    if (count % 14 == 0) {
      int num = stoi(frames);
      pair<int, string> p1(num, temp);
      list->insertLast(p1);
      temp = "";
      getline(myFile, frames);
    } 
    else if (count % 14 != 0) {
      getline(myFile, data);
      temp += data + "\n";
    }
    count++;
  } 
  //LinkedList<pair<int, string>>* scenes = list;
  return list;
  //return scenes;
}

void playMovie(List<pair<int, string>>* list) {

  int num = list->getSize();    // gets number of frames in movie

  // iterates over length of list to grab and print each frame in the scene
  for (int i=0; i<num; i++) {
    pair<int, string> frame = list->get(i);
    cout << frame.second << endl;
    //print each frame for the amount of frames then clear the image
    usleep(1000000/15 * frame.first);
    system("clear");
  }

  delete list;
}

