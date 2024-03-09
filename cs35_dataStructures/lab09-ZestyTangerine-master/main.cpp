/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "inroadsGame.h"
#include "inroadsGUI.h"
#include "ioUtils.h"

using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument: name of map file." << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line argument.
    string mapFilename = string(argv[1]);

    // Read the Inroads map file.
    pair<Graph<string, bool, int>*, Dictionary<string, pair<int, int>>*>
        mapFileContents;
    try {
        mapFileContents = readInroadsMap(mapFilename);
    } catch (exception e) {
        cout << "Could not read Inroads map file " << mapFilename << ": "
             << e.what() << endl;
    }
    // The map file contained the graph representing the map.  It also contained
    // the vertex positions (so we know where each vertex goes on the map).
    Graph<string, bool, int>* graph = mapFileContents.first;
    Dictionary<string, pair<int, int>>* vertexPositions =
        mapFileContents.second;

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object; do NOT change the type of this variable.
    InroadsGUI gui(vertexPositions, mapFilename);

    // Tell the GUI about the graph we have.
    gui.updateInroadsMap(graph);
    gui.updateScoreText("Score: 0");
    gui.updateTurnText("Turn: 1");
    int score = 0;

    // TODO: Write code that runs the game.  You'll want to write most of your
    // game logic into the InroadsGame class and then use an object of that type
    // here to control the game and relay what it says to the GUI.  This
    // assignment is more open-ended than the previous assignments.
    InroadsGame game(graph);
    
    while (game.turnsRemaining() == true) {
        // gets next move and checks that road is not already improved
        pair<string, string> temp = gui.getNextMove();

        if (temp.first == "" && temp.second == "") {
            break;     
        }

        Edge<string, bool, int> road = game.getRoad(temp);  
        
        while (road.getLabel() == true) {
            gui.updateMessage("Please select an unimproved road.");
            temp = gui.getNextMove();
            road = game.getRoad(temp);      
        }

        // improves selected road
        game.improveRoad(road);
        gui.updateMessage("Road improved !!");

        // calculates points earned this round
        int libPoints = game.getLibraryPoints();
        int storePoints = game.getStorePoints();
        int medPoints = game.getMedicalPoints();
        int totalPoints = libPoints + storePoints + medPoints;

        // update interface 
        gui.updateInroadsMap(graph);

        // update message with score summary from the turn
        string scoreMsg = "Your score this turn:\n   +" +to_string(libPoints)
        + " from the library\n   +" +to_string(storePoints)+ 
        " from stores\n   +"  + to_string(medPoints) + " from medical access\n"
        + "Total points this turn: " + to_string(totalPoints);
        gui.updateMessage(scoreMsg);

        // updates score text
        score += totalPoints;
        string scoreTxt = "Score: " + to_string(score);
        gui.updateScoreText(scoreTxt);

        // updates turn text
        int turn = game.getTurn();
        string turnTxt = "Turn: " + to_string(turn);
        gui.updateTurnText(turnTxt);

    }

    delete graph;
    delete vertexPositions;
    return 0;
}
