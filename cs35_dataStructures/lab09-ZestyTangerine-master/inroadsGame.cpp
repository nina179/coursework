/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include <string.h>

#include "inroadsGame.h"
#include "adts/stlHashTable.h"
#include "adts/dictionary.h"
#include "adjacencyListUndirectedGraph.h"


using namespace std;

// TODO: implement your InroadsGame class constructor and methods here

InroadsGame::InroadsGame(Graph<string, bool, int>* graph) {
  this->graph = graph;
  this->turn = 1;
}

InroadsGame::~InroadsGame() {
}

bool InroadsGame::turnsRemaining() {
  if (this->turn <= 20) {
    return true;
  } else {
    return false;
  }
}

int InroadsGame::getTurn() {
  return this->turn;
}

Edge<string, bool, int> InroadsGame::getRoad(pair<string, string> move) {
  string start = move.first;
  string end = move.second;

  // grabs selected edge from graph
  Edge<string, bool, int> road = this->graph->getEdge(start, end);


  return road;
}

void InroadsGame::improveRoad(Edge<string, bool, int> road) {
  string roadSrc = road.getSource();
  string roadDest = road.getDestination();
  int roadWeight = road.getWeight();

  // removes edge representing unimproved road
  this->graph->removeEdge(roadSrc, roadDest);

  // inserts edge representing improved road
  this->graph->insertEdge(roadSrc, roadDest, true, roadWeight);

  this->turn += 1;
}



int InroadsGame::getLibraryPoints() {
  Graph<string, bool, int>* graph = makeTempGraph();
  int points = 0;
  pair<vector<string>, vector<string>> temp = getPlaces('L');
  vector<string> residences = temp.first;
  string library = temp.second[0];
  for (int i = 0; i < residences.size(); i++){
    if (reachableDFS(residences[i],library, graph)){
      points += 15;
    }
  }
  delete graph;
  return points;
}

int InroadsGame::getStorePoints() {
  Graph<string, bool, int>* graph = makeTempGraph();
  int points = 0;
  pair<vector<string>, vector<string>> temp = getPlaces('S');
  vector<string> residences = temp.first;
  vector<string> stores = temp.second;
  for (int i = 0; i < residences.size(); i++) {
    for (int j = 0; j < stores.size(); j++) {
      if (reachableDFS(residences[i], stores[j], graph)){
        vector<string> path = shortestLengthPathBFS(residences[i], 
        stores[j], graph);
        if (path.size() <= 3) {
          points += 10;
        }
      }
    }
  } 
  delete graph;
  return points;
}

int InroadsGame::getMedicalPoints() {
  Graph<string, bool, int>* graph = makeTempGraph();
  int points = 0;
  pair<vector<string>, vector<string>> temp = getPlaces('M');
  vector<string> residences = temp.first;
  vector<string> hospitals = temp.second;
  Dictionary<string, int>* table;
  int time;
  for (int i = 0; i < residences.size(); i++) {
    table = singleSourceShortestPath(residences[i], graph);
    for (int j = 0; j < hospitals.size(); j++) {
      if (table->contains(hospitals[j])) {
        time = table->get(hospitals[j]);
        points += (420/time);
      }
    }
    delete table;
  }  
  delete graph;
  return points;
}

pair<vector<string>, vector<string>> InroadsGame::getPlaces(char search) {
  vector<string> allVertices = this->graph->getVertices();
  vector<string> residences, destinations;
  char firstChar;
  for (int i = 0; i < allVertices.size(); i++) {
    string word = allVertices[i];
    firstChar = word[0];
    if (firstChar == 'R') {
      residences.push_back(word);
    }
    if (firstChar == search) {
      destinations.push_back(word);
    }
  }
  pair<vector<string>, vector<string>> result;
  result.first = residences;
  result.second = destinations;
  return result;
}

Graph<string, bool, int>* InroadsGame::makeTempGraph() {
  Graph<string, bool, int>* tempGraph = 
  new AdjacencyListUndirectedGraph<string, bool, int>();
  
  vector<string> verticies = this->graph->getVertices();
  for (int j = 0; j < verticies.size(); j++) {
    tempGraph->insertVertex(verticies[j]);
  }

  vector<Edge<string, bool, int>> edges = this->graph->getEdges();
  for (int i = 0; i < edges.size(); i++) {
    if (edges[i].getLabel() == true) {
      tempGraph->insertEdge(edges[i].getSource(), edges[i].getDestination(), 
      edges[i].getLabel(), edges[i].getWeight());
    }
  }
  return tempGraph;
}