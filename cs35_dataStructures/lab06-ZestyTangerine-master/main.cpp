/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {

    // checks that program has required number of elements
    if (argc != 3) {
      cout << "[ERROR] this program takes two arguments" << endl;
      return 1;
    }

    // gets name of file and selected search method
    string mazeFile = argv[1];
    string searchMethod = argv[2];

    // reads map file using loadMap

    Maze* maze;
    try {
      Maze* maze = loadMap(mazeFile);
    } catch (runtime_error e) {
      cout << "[ERROR] invalid file name" << endl;
      return 1;
    }

    // solves maze based on selected search method
    cout << "solving maze..." << endl;
    List<Position*>* ans;
    if (searchMethod == "depth") {
      List<Position*>* ans = maze->solveDepthFirst();
    } else if (searchMethod == "breadth") {
      List<Position*>* ans = maze->solveBreadthFirst(); 
    } else {
      cout << "[ERROR] invalid search method" << endl;
      return 1;
    }

    // produce string containing solution using renderAnswer
    string answer = renderAnswer(maze, ans);
    cout << answer << endl;

    return 0;
}
