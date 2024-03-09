/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "point.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y, char symbol) {
  // initializes variables
  this->x = x;
  this->y = y;
  this->symbol = symbol;
}

void Point::draw(Grid* grid){
  // places symbol on specified (x,y) point on the grid 
  grid->placeSymbol(this->x, this->y, this->symbol);
}