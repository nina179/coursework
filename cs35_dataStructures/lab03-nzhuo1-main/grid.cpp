/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "grid.h"
#include <iostream>

using namespace std;

Grid::Grid() {
    // Initialize variables
    this->width = 20;
    this->height = 10;
    this->backgroundSymbol = '*';
    // Allocate memory
    this->data = new char[this->width * this->height];
    for (int i = 0; i < this->width * this->height; i++) {
        this->data[i] = this->backgroundSymbol;
    }
}

Grid::~Grid() {
    delete[] this->data;
}

void Grid::placeSymbol(int x, int y, char s) {
    this->data[x + y * this->width] = s;
}

string Grid::toString() {
    string s = "";
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            s += this->data[x + y * this->width];
            s += ' ';
        }
        s += '\n';
    }
    return s;
}

void Grid::print() {
    cout << this->toString();
}
