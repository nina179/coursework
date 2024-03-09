/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <iostream>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {
  this->width = width;
  this->height = height;

  this->positions = new Position**[width];         // creates width number of columns
  for (int x=0; x<width; x++){                     // adds hieght number of rows
    this->positions[x] = new Position*[height];
    for (int y=0; y<height; y++){                  // creates Position object for each cell in grid
      this->positions[x][y] = new Position(x,y);
    }
  }
}

Maze::~Maze() {
  for (int x=0; x<this->width; x++) {
    for (int y=0; y<this->height; y++) {
      delete this->positions[x][y];   // deletes each cell in grid
    }
    delete this->positions[x];        // deletes height number of rows
  }

  delete this->positions;             // deletes width number of columns
}

int Maze::getWidth() {
  return this->width;
}

int Maze::getHeight() {
  return this->height;
}

bool Maze::isWall(int x, int y) {
  if (this->positions[x][y]->isWall() == true) { 
    return true;
  } else {
    return false;
  }
}

void Maze::setWall(int x, int y) {
  this->positions[x][y]->setWall();
}

List<Position*>* Maze::getNeighbors(Position* position) {

  // creates empty STL list to store neighbors
  List<Position*>* neighbors = new STLList<Position*>();

  // gets x and y cooridates of position
  int x = position->getX();
  int y = position->getY();

  // appends down to neighbors if down is not out of bounds
  if (y-1 >= 0) {
    Position* down = this->positions[x][y-1];
    neighbors->insertFirst(down);
  }

  // appends right to neighbors if down is not out of bounds
  if (x+1 <= (this->width-1)) {
      Position* right = this->positions[x+1][y];
      neighbors->insertFirst(right);
  }

  // appends left to neighbors if down is not out of bounds
  if (x-1 >= 0) {
    Position* left = this->positions[x-1][y];
    neighbors->insertFirst(left);
  }

  // appends up to neighbors if down is not out of bounds
  if (y+1 <= this->height-1) {
    Position*  up = this->positions[x][y+1];
    neighbors->insertFirst(up);
  }

  return neighbors;
}

List<Position*>* Maze::solveBreadthFirst() {  
  OrderedCollection<Position*>* mazeQ = new LinkedQueue<Position*>();
  List<Position*>* finalQ = solve(mazeQ);
  return finalQ;
}

List<Position*>* Maze::solveDepthFirst() {
  OrderedCollection<Position*>* mazeStack = new LinkedStack<Position*>();
  List<Position*>* finalStack = solve(mazeStack);
  return finalStack;
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {

  // saves start and exit points for easy reference
  Position* start = this->positions[0][0];
  Position* exit = this->positions[this->width-1][this->height-1];

  // insert start position into mazeQ and mark as visited
  Position* current = start;
  exploration->insert(current);
  current->setVisited();

  // visits each available space in maze
  while (exploration->getSize() > 0) {
    current = exploration->remove();    
    if (current == exit) { 
      break;
    } else {        
      List<Position*>* neighbors = getNeighbors(current);
      for (int i=0; i<neighbors->getSize(); i++) {
        Position* check = neighbors->get(i);
        if (check->isVisited() == false && check->isWall() == false) {
          check->setVisited();
          check->setPrevious(current);
          exploration->insert(check);
        }
      }
    }
  }

  // walks backwards from exit to start using current's previous if exit is visited
  if (exit->isVisited() == true) {
    List<Position*>* path = new STLList<Position*>();
    while (current->getPrevious() != nullptr) {
      path->insertFirst(current);
      current = current->getPrevious();
    }
    path->insertFirst(start);
    return path;
  } else {      // returns nullptr in event that no exit is found
    return nullptr;
  }
}