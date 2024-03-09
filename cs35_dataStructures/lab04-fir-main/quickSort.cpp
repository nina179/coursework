/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "quickSort.h"
int partition(int *array, int left, int right);

void quickSort(int *array, int startIndex, int endIndex) {
  int size = endIndex - startIndex + 1;
  if (size>1) {
    int pivotIndex = partition(array, startIndex, endIndex);
    quickSort(array, startIndex, pivotIndex-1);
    quickSort(array, pivotIndex+1, endIndex);
  }
}

int partition(int *array, int left, int right) {

  int i = left;
  int j = right - 1;
  int pivot = array[right];

  while (i<j) {
    while (i<j && array[i]<=pivot) {
      i = i + 1;
    } 
    while (i<j && array[j]>=pivot) {
      j = j - 1;
    }
    if (i != j) {
      int temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }
  
  if (array[i] >= array[right]) {
    int temp_sec = array[i];
    array[i] = array[right];
    array[right] = temp_sec;
    return i;
  } else {
    return right;
  }
}

// You should not need to modify this function.
// qSort is a wrapper around the main quickSort function.
void qSort(int *array, int size) {
  quickSort(array, 0, size - 1);
}
