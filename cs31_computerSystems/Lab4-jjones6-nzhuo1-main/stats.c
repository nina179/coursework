/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

/* 
 *  This program reads in floats from a file and prints out statistics
 *  about about the values in the file 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readfile.h"

// N: start size for first dynamically allocated array of values
#define N             20
// MAXFILENAME: max length of input file name string + 1 (includes '\0')
#define MAXFILENAME   256
// you can add your own constants (using #define) here if needed/desired

// function prototypes
float *get_values(int *size, int *capacity, char *filename);
void ensureCapacity(float *values, int *size, int *capacity);
void sortArray(float *array, int *size);
void swap(float *array, int a, int b);
float getMean(float *array, int *size);
double getStddev(float *array, int *size, float avg);
void printStats(float *array, int *size, int *capacity, float median);
// TODO: add more function prototypes here:

/**********************************************************************/
int main(int argc, char *argv[]) {

  char filename[MAXFILENAME];
  float *vals = NULL;
  int size, capacity;

  // this code checks command line args to make sure program was run
  // with filename argument.  If not, calls exit to quit the program
  if (argc != 2) {
    printf ("usage: %s filename\n", argv[0]);
    exit(1);
  }
  // this copies the filename command line argument into the 
  // string variable filename
  strncpy(filename, argv[1], MAXFILENAME-1);

  // call get_values function:
  vals = get_values(&size, &capacity, filename);

  // gets median of array before sorting
  float median = vals[(size-1)/2];

  // sort floats in vals
  sortArray(vals, &size);

  // prints out stats of array vals
  printStats(vals, &size, &capacity, median);

  free(vals);
  return 0;
}

/************************************************************************/
/* This function displays stats of the floats in array using defined
 * helper functions
 *
 *    array: pointer to a sorted array of floats
 *    size: number of floats in array
 *    capacity: total number of buckets in array
 *
 *    returns: nothing
 */
void printStats(float* array, int *size, int *capacity, float median) {

  printf("Results: \n");
  printf("---------\n");

  // prints number of values in array
  printf("num values: %17d\n", *size);

  // prints smallest value in array
  float min = array[0];
  printf("min: %24.3f\n", min);

  // prints largest value in array
  float max = array[*size-1];
  printf("max: %24.3f\n", max);

  // prints average of values in array
  float avg = getMean(array, size);
  printf("mean: %23.3f\n", avg);

  // prints median of values in array
  printf("median: %21.3f\n", median);

  // prints standard deviation of values in array
  double stddev = getStddev(array, size, avg);
  printf("std dev: %20.3f\n", stddev);

  // prints unused buckets in array
  int unused = *capacity - *size;
  printf("unused array capacity: %6d\n", unused);
}

/**********************************************************************/
/* This function reads in values from the input file into a dynamically
 * allocated array of floats that it returns.  It uses a doubling 
 * algorithm to increase the size of the array as it needs more space
 * for the values read in from the file.
 * 
 *   size: set to the number of data values read in from the file
 *   capacity: set to the total number of buckets in the returned array
 *   filename: the name of the file to open
 *
 *   returns: the base address of the array of values read in 
 *            or NULL on error
 */
float *get_values(int *size, int *capacity, char *filename) {

  float *array = NULL;
  float x;
  int ret;

  // initialize array with capacity for 20 floats
  array = malloc(N * sizeof(float));
  *size = 0;
  *capacity = N;

  // open the file
  ret = open_file(filename);
  if (open_file(filename)) {  
    return NULL;
  }
  
  ret = read_float(&x);     // attempts to read first float from file
  int i = 0;    // keeps track of array index
  while (ret != -1){
    // reads float from file into array
    array[i] = x;
    i++;

    // increments size and ensures capacity
    *size += 1;
    if(*size == *capacity) {
      ensureCapacity(array, size, capacity);
    }

    // checks if theres another float to read in from file
    ret = read_float(&x);
  }

  close_file();  // close the file
  return array;   // return the values array
}

/* This function copies values from a full array into a new array double the
 * size, then updates the capacity using the "pass by pointer" parameter.
 *
 *    values: a full array of floats
 *    size: set to total number of floats in full array
 *    capacity: updates to match the total number of buckets in values
 *
 *    returns: nothing
 */
void ensureCapacity(float *values, int *size, int *capacity) {
  
  // creates new array with double the capacity
  *capacity *= 2;
  float *new = NULL;       
  new = malloc(*capacity *sizeof(float));

  // copy values from old array into new new array
  for (int i=0; i < *size; i++){
    new[i] = values[i];
  }

  values = new;
  free(new);
}

/* This function sorts the floats in the pass by pointer array parameter  
 * in place using selection sort
 *  
 *    array: pointer to an unsorted array of floats
 *    size: integer value representing number of floats in array
 *
 *    returns: nothing
 */
void sortArray(float *array, int *size) {

  // selection sort algorithm
  for (int i = 0; i < *size; i++){
    int min = i;
    for (int j = i+1; j < *size; j++){
      if (array[j] < array[min]){
        min = j;
      }
    }
    swap(array, i, min);
  }
}

/* This funciton swaps the value in index a of the pass by pointer array
 * parameter with the value in index b in the same array
 *
 *    array: pointer to an unsorted array
 *    a: integer representing index of the array to be swapped with b 
 *    b: integer representing index of the array to be swapped with a
 *
 *    returns: nothing
 */
void swap(float *array, int a, int b) {
  float temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

/* This funciton calculates the average values of the floats in array
 *
 *    array: pointer to an array with size number of floats
 *    size: integer value representing number of floats in array
 *
 *    returns: float value representing average of all values in array
 */
float getMean(float *array, int *size) {
  float sum;
  double avg;  
  
  // sum up value of floats in array
  sum = 0;
  for(int i = 0; i < *size; i++){
    sum += array[i];
  }

  // calculate average
  avg = sum / *size;

  return avg;
}

/* This function calculates the standard deviation of the floats in the 
 * pass by pointer array paramter
 *
 *    array: pointer to an array with n number of floats
 *    n: integer value representing number of floats in array
 *    avg: float representing average of all floats in array
 *
 *    returns: float value representing standard deviation of array
 */
double getStddev(float *array, int *size, float avg) {
  float x, sum, n;
  double stddev;
  
  // iterate over length of array to solve summation
  sum = 0;
  for(int i = 0; i < *size; i++){
    x = array[i] - avg;
    sum += x*x;
  }

  // calculate standard deviation
  n = *size - 1;
  n = 1/n;
  n = n * sum;

  stddev = sqrt(n);

  return stddev;
}