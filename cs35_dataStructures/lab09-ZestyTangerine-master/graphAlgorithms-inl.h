/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <string>
#include "adts/stlQueue.h"
#include "adts/dictionary.h"
#include "adts/stlHashTable.h"
#include "adts/stlMinPriorityQueue.h"
#include "adts/stlStack.h"
#include "adts/stlList.h"


template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    STLStack<V> stack;
    STLHashTable<V, bool> visited;
    V current;
    vector<V> neighbors;
    stack.push(src);
    visited.insert(src, true);
    while (!stack.isEmpty()) {
        current = stack.pop();
        if (current == dest) {
            return true;
        }
        neighbors = g->getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++) {
            if (!visited.contains(neighbors[i])) {
                stack.push(neighbors[i]);
                visited.insert(neighbors[i], true);
            }
        }
    }
    return false;
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    if (!reachableDFS(src, dest, g)){
        throw runtime_error("Can't reach dest from src!");
    }

    V current;
    STLList<V> path; 
    vector<V> finalPath;
    vector<V> neighbors;
    STLQueue<V> q;
    STLHashTable<V, V> previous;
    q.enqueue(src);
    previous.insert(src, src);
    while (!q.isEmpty()){
        current = q.dequeue();
        if (current == dest) { //found dest!
            while (current != src){
                path.insertFirst(current);
                current = previous.get(current);
            }
            path.insertFirst(src);
            for (int j = 0; j < path.getSize(); j++){
                finalPath.push_back(path.get(j));
            }
            return finalPath;
        }
        else {
            neighbors = g->getNeighbors(current);
            for (int i = 0; i < neighbors.size(); i++) {
                if (!previous.contains(neighbors[i])) {
                    previous.insert(neighbors[i], current);
                    q.enqueue(neighbors[i]);
                }
            }
        }
    }
    return finalPath; //empty path

}


template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    STLMinPriorityQueue<W, V> exploration;
    exploration.insert(0, src);
    STLHashTable<V, W>* costs = new STLHashTable<V, W>;     // fixed
    costs->insert(src, 0);
    while (!exploration.isEmpty()) {
        V current = exploration.remove();
        W currentCost = costs->get(current);
        vector<Edge<V, E, W>> outgoing = g->getOutgoingEdges(current);
        for (int i = 0; i < outgoing.size(); i++) {
            V neighbor = outgoing[i].getDestination();
            W newCost = currentCost + outgoing[i].getWeight();
            if (!costs->contains(neighbor)) {
                costs->insert(neighbor, newCost);
                exploration.insert(newCost, neighbor);
            }
            else if (costs->get(neighbor) > newCost) {
                costs->update(neighbor, newCost);
                exploration.insert(newCost, neighbor);
            }
        }
    }
    return costs;
}