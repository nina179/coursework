/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "horizontalLine.h"

HorizontalLine::HorizontalLine(int x, int y, int length, char symbol) {
  // initializes variables 
  this->x = x;
  this->y = y;
  this->length = length;
  this->symbol = symbol;
}

void HorizontalLine::draw(Grid* grid){

  // places symbols on the specified x point in y row on the grid 
  for (int i=0; i<(this->length); i++) {
      grid->placeSymbol(this->x+i, this->y, this->symbol);
  }
}