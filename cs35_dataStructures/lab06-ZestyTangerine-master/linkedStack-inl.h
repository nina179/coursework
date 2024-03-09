/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedStack.h"

using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedStack<T>::LinkedStack() {
}

template <typename T> void LinkedStack<T>::push(T element) {
  this->list.insertFirst(element);
}

template <typename T> T LinkedStack<T>::pop() {
  T val = this->list.removeFirst();
  return val;
}

template <typename T> void LinkedStack<T>::insert(T element) {
  this->push(element);
}

template <typename T> T LinkedStack<T>::remove() {
  T val = this->pop();
  return val;
}

template <typename T> int LinkedStack<T>::getSize() {
  int size = this->list.getSize();
  return size;
}

template <typename T> bool LinkedStack<T>::isEmpty() {
  bool temp = this->list.isEmpty();
  return temp;
}

template <typename T> T LinkedStack<T>::peek() {
  T val = this->list.getFirst();
  return val;
}
