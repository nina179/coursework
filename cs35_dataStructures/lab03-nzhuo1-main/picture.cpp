/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms

  draws shapes onto grid and prints them out
*/

#include <iostream>
#include <stdexcept>

#include "picture.h"

using namespace std;

Picture::Picture() {
    // constructs array of up to 50 Shape pointers
    this->numberOfShapes = 0;
    this->shapes = new Shape*[50];
}

Picture::~Picture() {
    // deletes every shape in shapes[] array
    for (int i=0; i<(this->numberOfShapes); i++) {
        delete this->shapes[i];
    }

    // deletes shapes array
    delete[] this->shapes;
}

string Picture::toString() {
    // creates grid
    Grid* grid = new Grid();

    // places shapes on Grid
    for (int i=0; i<(this->numberOfShapes); i++) {
        (this->shapes[i])->draw(grid);
    }

    // converts grid to string
    string s = grid->toString();

    // deletes memory allocated for grid
    delete grid;

    // returns grid as string
    return s;
}

void Picture::print() {
    // prints out grid as string
    cout << this->toString() << endl;
}

void Picture::addShape(Shape* shape) {
    // adds shape to this->shapes array
    this->shapes[this->numberOfShapes] = shape;

    // tallies up number of shapes in array
    this->numberOfShapes += 1;
}
