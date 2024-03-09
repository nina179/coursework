/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>

#include "quickSort.h"

using namespace std;

TEST(threeElements) {
  // Create a static array containing the numbers 4, 8, 6.
  int array[3] = {4, 8, 6};
  quickSort(array, 0, 2);
  CHECK_EQUAL(4, array[0]);
  CHECK_EQUAL(6, array[1]);
  CHECK_EQUAL(8, array[2]);
}

TEST(reverseSorted) {
  int size = 20;
  // Create a dynamically-allocated array
  int *array = new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = size - 1 - i;
  }
  quickSort(array, 0, size - 1);
  for (int i = 0; i < size; i++) {
    CHECK_EQUAL(i, array[i]);
  }
  // de-allocate array
  delete[] array;
  array = nullptr;
}

TEST(singleElement) {
  // Create a static array containing one single element: 2.
  int array[1] = {2};
  quickSort(array, 0, 0);
  CHECK_EQUAL(2, array[0]);
}

TEST(preSorted) {
  // Create a static array containing the numbers 0, 1, 2, 3, 4.
  int array[5] = {0, 1, 2, 3, 4};
  quickSort(array, 0, 4);
  for (int i = 0; i < 5; i++) {
    CHECK_EQUAL(i, array[i]);
  }
}

TEST(duplicateSort) {
  // Create a static array containing the numbers 0, 1, 1, 2, 3.
  int array[5] = {0, 1, 1, 2, 3};
  quickSort(array, 0, 4);
  CHECK_EQUAL(0, array[0]);
  CHECK_EQUAL(1, array[1]);
  CHECK_EQUAL(1, array[2]);
  CHECK_EQUAL(2, array[3]);
  CHECK_EQUAL(3, array[4]);
}

TEST(alternateMid) {
  /* Create a dynamically-allocated array containing 1000 numbers
   * that approach a midpoint from opposite directions.
   */
  int *array = new int[1000];
  for (int i=0; i<500; i++) {
    array[i*2] = i;
    array[(i*2)+1] = 999-i;
  }
  quickSort(array, 0, 999);
  for (int i=0; i<1000; i++) {
    CHECK_EQUAL(i, array[i]);
  }
  // de-allocate array
  delete[] array;
  array = nullptr;
} 

/* no need to modify main */
int main() {
  return UnitTest::RunAllTests();
}
