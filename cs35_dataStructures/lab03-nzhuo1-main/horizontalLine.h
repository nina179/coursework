#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "shape.h"
#include <iostream>

using namespace std;

// TODO: Declare your HorizontalLine class here.

class HorizontalLine:public Shape {
  private:
    int x; 
    int y;
    int length;
    char symbol;

  public:
    // tells where to place symbols on the grid
    HorizontalLine(int x, int y, int length, char symbol);

    // displays symbol onto the grid at appropriate location
    void draw(Grid* grid);   
};