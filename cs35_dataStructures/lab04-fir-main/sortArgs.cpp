/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

/*
You do NOT need to modify this program!

This program can be used to test your sorting algorithm.
It takes a sequence of numbers from the command line, stores
the numbers into an array, quick sorts the array, and then
displays the final array contents.
*/

#include <iostream>
#include <string>

#include "quickSort.h"

using namespace std;

/**
 * Pretty prints an array
 * @param array The array to print
 * @param size the size of the array
 */
void printArray(int arr[], int size);

int main(int argc, char** argv) {
  int arrsize = argc-1;
  int *array = new int[arrsize];

  for (int i=0; i<arrsize; i++) {
    array[i] = stoi(argv[i+1]);
  }

  printArray(array, arrsize);
  qSort(array, arrsize);
  printArray(array, arrsize);

  delete[] array;
  array = nullptr;
  return 0;
}

void printArray(int arr[], int size) {
  if (size <= 0) {
    cout << "[]" << endl;
    return;
  }

  cout << "[" << arr[0];
  for (int i = 1; i < size; i++) {
    cout << ", " << arr[i];
  }
  cout << "]" << endl;
}
