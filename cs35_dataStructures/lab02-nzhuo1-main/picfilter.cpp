/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms

  This program takes in a .ppm file and creates a new one after 
  performing a specific image transformation
*/

#include <iostream>
#include <string>

#include "image.h"
#include "ppmio.h"

using namespace std;

int main(int argc, char** argv) {

  // takes file names from argv and checks number of arguments
  if (argc != 4) {
    cout << "[SYNTAX ERROR]" << endl;
    cout << "There should be three arguments." << endl;
    return 1;
  }

  // saves each given argument as a string 
  string oldfile;
  string filter;
  string newfile;

  oldfile = argv[1];
  filter = argv[2];
  newfile = argv[3];
  
  // uses ppmio.h to read the width and height of given .ppm file
  int width;
  int height;

  width = ppm_width(oldfile);
  height = ppm_height(oldfile);

  // uses width and height to find total number of pixels
  int p_num;
  p_num = width * height;

  // creates dynamic array pixels[] and reads rbg values into the array
  int *pixels = new int[p_num];
  pixels = read_ppm(oldfile);

  // uses filter argument to know what function from image.cpp to call
  if (filter == "noRed") {
    cout << "Running noRed()..." << endl;
    noRed(width, height, pixels);
  } else if (filter == "noGreen") {
    cout << "Running noGreen()..." << endl;
    noGreen(width, height, pixels);
  } else if (filter == "noBlue") {
    cout << "Running noBlue()..." << endl;
    noBlue(width, height, pixels);
  } else if (filter == "invert") {
    cout << "Running invert()..." << endl;
    invert(width, height, pixels);
  } else if (filter == "grayscale") {
    cout << "Running grayscale()..." << endl;
    grayscale(width, height, pixels);
  } else if (filter == "flipHorizontally") {
    cout << "Running flipHorizontally()..." << endl;
    flipHorizontally(width, height, pixels);
  } else if (filter == "flipVertically") {
    cout << "Running flipVertically()..." << endl;
    flipVertically(width, height, pixels);
  } else {
    cout << "[SYSTEM ERROR]" << endl;
    cout << "This is an invalid transformation." << endl;
    return 1;
  }

  // saves filtered .ppm image as a new .ppm file
  write_ppm(newfile, width, height, pixels);

  delete[] pixels;
  return 0;
}