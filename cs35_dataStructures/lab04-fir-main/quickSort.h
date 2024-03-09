#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

/**
 * Performs the main quick sort algorithm to sort the provided array.
 * @param array The array to sort.
 * @param startIndex The leftmost index (inclusive) of the part of the array
 *                   to sort.
 * @param endIndex The rightmost index (inclusive) of the part of the array
 *                 to sort.
 */
void quickSort(int* array, int startIndex, int endIndex);

/**
 * Wrapper function around the main quickSort function.
 * This function should get called once, then call quickSort
 *   with indices 0, size-1.
 * @param array The array to sort.
 * @param size  The size of the array.
 */
void qSort(int *array, int size);
