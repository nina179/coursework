/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

using std::runtime_error;

// This file defines the methods for two classes: LinkedListNode and LinkedList.
// The LinkedListNode methods have been defined for you.  You are responsible
// for defining the LinkedList methods.

////////// LinkedListNode /////////////////////////////////////////////////////

template <typename T>
LinkedListNode<T>::LinkedListNode(T val, LinkedListNode<T>* next) {
    this->value = val;
    this->next = next;
}

////////// LinkedList /////////////////////////////////////////////////////////


template <typename T> LinkedList<T>::LinkedList() {
    // initailizes variables
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T> LinkedList<T>::~LinkedList() {
    // repeatedly calls removeFirst() until LinkedList is empty
    int size = this->size;
    for (int i=0; i<size; i++) {
            this->removeFirst();
    }
}

template <typename T> void LinkedList<T>::checkInvariants() {
    if (this->size == 0) { 
        // ensures LinkedList is empty when size = 0
        this->head = nullptr;
        this->tail = nullptr;
    } else {

        // counts up number of not empty nodes
        int count = 0;
        LinkedListNode<T>* p = this->head;
        while (p != nullptr) {
            p = p->next;
            count ++;
        }
        
        // throws runtime error if number of nodes in LinkedList do not match this->size
        if (this->size != count) {
            throw runtime_error("LinkedList::checkInvariants() | number of LinkedListNodes not equal to Size");
        }  
    }
}

template <typename T> int LinkedList<T>::getSize() {
    // returns integer that tells number of not empty LinkedListNodes
    return this->size;
}

template <typename T> bool LinkedList<T>::isEmpty() {
    // returns true if size = 0 and false when size > 0
    if (this->size == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T> T LinkedList<T>::getFirst() {

    // returns value stored in this->head if LinkedList is not empty
    if (this->isEmpty() == false){
        return this->head->value;
    } else {
        throw runtime_error("LinkedList::getFirst() | LinkedList is empty");
    }
}

template <typename T> T LinkedList<T>::getLast() {
    // returns value stored in this->tail head if LinkedList is not empty
    if (this->isEmpty() == false){
        return this->tail->value;
    } else {
        throw runtime_error("LinkedList::getLast() | LinkedList is empty");
    }
}

template <typename T> T LinkedList<T>::get(int index) {

    // counts up number until we get to index of specified node
    int count = 0;
    LinkedListNode<T>* p = this->head;
    // throws runtime error if requested index is not a positive number between 0 and this->size
    if (0 <= index && index < this->size) {
        while (p != nullptr && count < index) {
            p = p->next;
            count ++;
        }      
    } else {
        throw runtime_error("LinkedList::get() | index out of range");
    }

    // returns value of indexed node
    return p->value;
}

template <typename T> void LinkedList<T>::insertFirst(T value) {
    // creates new LinkedListNode storing new value and pointing to the old this->head node
    LinkedListNode<T>* newHead = new LinkedListNode<T>(value, this->head);

    // sets new LinkedListNode as the new head
    this->head = newHead;

    // also sets new LinkedListNode as this->tail when LinkedList is empty
    if (this->size == 0) {
        this->tail = newHead;
    }

    // increases size of LinkedList by 1
    this->size++;
}

template <typename T> void LinkedList<T>::insertLast(T value) {
    // creates new LinkedListNode storing new value and pointing to the old this->tail node
    LinkedListNode<T>* newTail = new LinkedListNode<T>(value, nullptr);

    // also sets newTail as both this->head and this->tail when LinkedList is empty
    if (this->size == 0) {
        this->head = newTail;
        this->tail = newTail;
    } else {
        // links new tail to rest of list
        this->tail->next = newTail;

        // sets new LinkedListNode as the new tail
        this->tail = newTail;        
    }

    // increases size of LinkedList by 1
    this->size++;
}

template <typename T> T LinkedList<T>::removeFirst() {

    // initializes tempVal to be returned later
    T tempVal;
    

    if (this->size == 0) {
        // throws runtime error when trying to remove item from empty LinkedList
        throw runtime_error("LinkedList::removeFirst | LinkedList is empty");
    } else if (this->size == 1) {
        // saves value of this->head to tempVal and deletes the node it existed in
        LinkedListNode<T>* temp = this->head;
        tempVal = temp->value;
        delete temp;

        // initializes head and tail to reflect that LinkedList is empty
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        // saves value of this->head to tempVal
        LinkedListNode<T>* temp = this->head;
        tempVal = temp->value;

        // moves head forward to next node and deletes temporary node pointing to old this->head
        this->head = this->head->next;
        delete temp;
    }

    // decreases size of LinkedList by 1 and returns deleted value
    this->size--;
    return tempVal;
}

template <typename T> T LinkedList<T>::removeLast() {

    // initializes tempVal to be returned later
    T tempVal;

    if (this->size == 0) {
        // throws runtime error when trying to remove item from empty LinkedList
        throw runtime_error("LinkedList::removeLast | LinkedList is empty");
    } else if (this->size == 1) {
        // saves value of this->head to tempVal and deletes the node it existed in
        LinkedListNode<T>* temp = this->tail;
        tempVal = temp->value;
        delete temp;

        // initializes head and tail to reflect that LinkedList is empty
        this->head = nullptr;
        this->tail = nullptr;

    } else if (this->size >= 2) {
        // saves value of this->tail to tempVal
        LinkedListNode<T>* temp = this->tail;
        tempVal = temp->value;

        // walks down LinkedList until p is at the second to last node
        LinkedListNode<T>* p = this->head;
        for (int i=0; i<(this->size - 2); i++) {
            p = p->next;
        }        
        
        // sets last node to nullptr
        p->next = nullptr;
        
        // sets p to tail and deletes temporary node pointing to old this->tail
        this->tail = p;
        delete temp;
    }

    // decreases size of LinkedList by 1 and returns deleted value
    this->size--;
    return tempVal;
}