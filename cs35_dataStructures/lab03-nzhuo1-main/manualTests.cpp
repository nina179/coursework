/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "grid.h"
#include "shape.h"
#include "point.h"
#include "horizontalLine.h"
#include "verticalLine.h"
#include "rectangle.h"
#include "picture.h"
#include <iostream>

using namespace std;

int main() {
    // You can put anything you like here.  This file exists so that
    // you can experiment with your code.  For instance, the following
    // might be a useful test after you've written your Point class.

    
    Grid* grid = new Grid();
    Shape* s = new Rectangle(0, 0, 3, 3, '@');
    s->draw(grid);
    cout << grid->toString() << endl;
    delete grid;
    delete s;

    return 0;
}
