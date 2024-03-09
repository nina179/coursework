/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include <UnitTest++/UnitTest++.h>

#include "adjacencyListGraph.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/dictionary.h"
#include "adts/graph.h"
#include "graphAlgorithms.h"
#include "ioUtils.h"

using namespace std;

template <typename V, typename E, typename W,
          template <class, class, class> class G = AdjacencyListUndirectedGraph>
Graph<V, E, W>* makeGraph(vector<V> vertices, vector<Edge<V, E, W>> edges) {
    Graph<V, E, W>* graph = new G<V, E, W>();
    for (int i = 0; i < vertices.size(); i++) {
        graph->insertVertex(vertices.at(i));
    }
    for (int i = 0; i < edges.size(); i++) {
        Edge<V, E, W> edge = edges.at(i);
        graph->insertEdge(edge.getSource(), edge.getDestination(),
                          edge.getLabel(), edge.getWeight());
    }
    return graph;
}


int main(int argc, char** argv) {
  // You can use this main to experiment with the code you have written
  Graph<string, bool, int>* graph = makeGraph<string, bool, int>(
  {"start", "1", "2", "finish", "alt"}, {{"start", "1", false, 3},
                                          {"1", "2", false, 4},
                                          {"2", "finish", false, 2},
                                          {"start", "alt", false, 5},
                                          {"alt", "finish", false, 6}});
Dictionary<string, int>* results =
    singleSourceShortestPath(string("start"), graph);
    return 0;
}
