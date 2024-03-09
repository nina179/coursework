/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedQueue.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedQueue<T>::LinkedQueue() {
}

template <typename T> int LinkedQueue<T>::getSize() {
  int size = this->list.getSize();
  return size;
}

template <typename T> bool LinkedQueue<T>::isEmpty() {
  bool temp = this->list.isEmpty();
  return temp;
}

template <typename T> T LinkedQueue<T>::peek() {
  T val = this->list.getFirst();
  return val;
}

template <typename T> void LinkedQueue<T>::enqueue(T element) {
  this->list.insertLast(element);
}

template <typename T> T LinkedQueue<T>::dequeue() {
  T val = this->list.removeFirst();
  return val;
}

template <typename T> void LinkedQueue<T>::insert(T element) {
  // NOTE: for a hint on how to implement this, see LinkedStack<T>::insert
  this->enqueue(element);
}

template <typename T> T LinkedQueue<T>::remove() {
  T val = this->dequeue();
  return val;
}

