/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <string>

#include "graphAlgorithms.h"
#include "inroadsGUI.h"

/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */

class InroadsGame {
  public:
    /**
     * Class constructor for playing inroads game
     * @param graph Dynamically allocated graph object with map information
     */
    InroadsGame(Graph<std::string, bool, int>* graph);

    /**
     * Destructor for InroadsGame class
     */
    virtual ~InroadsGame();

    /**
     * Checks if there are turns remaining out of the alloted 20
     * @return Boolean value telling if there are turns remaining 
     */
    bool turnsRemaining();

    /**
     * Tells turn the game is on
     * @return Integer telling how many turns have been taken
     */
    int getTurn();

    /**
     * Ensures that chosen road has not already been improved
     * @return Edge that has been selected by user to be improved
     */
    Edge<std::string, bool, int> getRoad(pair<std::string, std::string> move);

    /**
     * Improves selected road
     * @param road Edge being improved
     */
    void improveRoad(Edge<std::string, bool, int> road);
    
    /**
     * Calculates points earned from library!
     * @return points earned from library
     */
    int getLibraryPoints();

    /**
     * Calculates points earned from store!
     * @return points earned from store
     */
    int getStorePoints();

    /**
     * Calculates points earned from hospital!
     * @return points earned from hospital
     */
    int getMedicalPoints();



  private:
    Graph<std::string, bool, int>* graph;
    int turn;

    
    pair<vector<std::string>, vector<std::string>> getPlaces(char search);
    Graph<std::string, bool, int>* makeTempGraph();

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  private:
    InroadsGame(const InroadsGame& other) = delete;
    InroadsGame& operator=(const InroadsGame& other) = delete;
};
