/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "helpers.h"

template <typename T> vector<T> dynamicListToStaticVector(List<T>* list) {
    vector<T> vectorToReturn;
    int listSize = list->getSize();
    for(int i = 0; i < listSize; i++) {
        vectorToReturn.push_back(list->removeFirst());
    }
    delete list;
    return vectorToReturn;
}
