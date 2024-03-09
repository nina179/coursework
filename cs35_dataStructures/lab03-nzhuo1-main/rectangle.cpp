/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms

  draws rectangles on grid
*/

#include "rectangle.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle(int x, int y, int width, int height, char symbol) {
  // initializes variables
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->symbol = symbol;
}

void Rectangle::draw(Grid* grid){

  // draws symbol starting at specified point for x columns
  for (int i=0; i<(this->width); i++) {
    // repeats above for y rows
    for (int j=0; j<(this->height); j++) {
      grid->placeSymbol(this->x+i, this->y+j, this->symbol);
    }
  }
}