/*
 * Swarthmore College, CS 31
 * Copyright (c) 2023 Swarthmore College Computer Science Department,
 * Swarthmore PA
 */

/*
 * Hi grader :) pls be nice to us
 
 * This program allows the user to choose a file with unsorted float values,
 * prints the values, sorts them, and then prints values after sorting.
 */

#include <stdio.h>      // the C standard I/O library
#include <stdlib.h>     // the C standard library
#include <string.h>     // the C string library
#include "readfile.h"   // my file reading routines

/* #define constant values here: */
#define MAXFILENAME  128
#define ARRAYSIZE    1000

/* function prototypes: */
void get_filename_from_cmdline(char filename[], int argc, char *argv[]);
void displayF(int size, float num[]);
void arraySort(int size, float array[]);
int checkSort(int size, float array[]);
void swap(float array[], int a, int b);

/********************************************************************/
int main (int argc, char *argv[]) {

  int ret;                    /* for storing function return values */
  char filename[MAXFILENAME]; /* the input filename  */
  float values[ARRAYSIZE];    /* stores values read in from file */

  int x, size;
  float f, min, max;

  /* initialize filename string from the command line arguments */
  get_filename_from_cmdline(filename, argc, argv);

  /* try to open file */
  ret = open_file(filename);
  if(ret == -1) {
    printf("ERROR: can't open %s\n", filename);
    /* exit quits the program immediately. Some errors are not 
     * recoverable. Exit with an error message to handle these cases. */
    exit(1);
  }

  //read in file header to get number of floats needed
  ret = read_int(&x);
  size = x;

  ret = read_float(&f);
  min = f;

  ret = read_float(&f);
  max = f;
  
  //the next two print statements states what file is being read and the size + min and max values in the file
  printf("Reading file %s\n", filename);
  printf("This file has %d floats ranging from %.2f to %.2f\n", size, min, max);

  //reads in floats from file  
  for (int i = 0; i < size; i++) {
    ret = read_float(&f);
    values[i] = f;
  }

  //prints out the unsorted values on a single line
  printf("The unsorted values are: ");
  displayF(size, values);

  //sorts the array in place using a function
  arraySort(size, values);

  //checks that the array is now sorted
  ret = checkSort(size, values);
  if (ret == -1) {
    printf("ERROR: sorting failed");    // exits program with error message
    exit(1);                            // if sorting fails
  }

  //prints out sorted values in the array
  printf("The sorted values are: ");
  displayF(size, values);

  close_file();  /* close file */
  return 0;
}

/***********************************************************/
/* swaps two indices
 *    a - first index to be swapped
 *    b - second index to be swapped
 *    array - the array containing float values
*/
void swap(float array[], int a, int b) {
  float temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

/* prints out floats for user
 *    num - array of floats to be displayed
 */
void displayF(int size, float num[]) {
    for (int i = 0; i < size; i++) {
      printf("%.2f ", num[i]);
    }
    printf("\n");
}

/* sorts array in place using selection sort
 *    size - integer representing size of array[]
 *    array - array of unsorted floats
 * returns nothing
 */
void arraySort(int size, float array[]) {
  for (int i = 0; i < size; i++) {
    int min = i;
    for (int j = i+1; j < size; j++) {
      if (array[j] < array[min]) {
        min = j;
      }
    }
    swap(array, i, min);
  }
  printf("\n");
}

/* checks that array is sorted
 *    size - integer representing size of array[]
 *    array - array of sorted floats
 * returns 0 if array is sorted and 1 if not sorted
 */
int checkSort(int size, float num[]) {
    for (int i = 1; i < (size-1); i++) {
      if (num[i-1] > num[i]) {
        return -1;
      } 
    }
    return 0;
}


/***********************************************************/
/* THE FOLLOWING FUNCTION IS PROVIDED FOR YOU
 * DO NOT MODIFY, OR DO SO AT YOUR OWN RISK!
 *
 * This function gets the filename passed in as a command line option
 * and copies it into the filename parameter. It exits with an error
 * message if the command line is badly formed.
 *
 *   filename: the string to fill with the passed filename
 *   argc, argv: the command line parameters from main
 *               (number and strings array)
 */
void get_filename_from_cmdline(char filename[], int argc, char *argv[]) {

  if(argc != 2) {
    printf("Usage: ./exp integer_file\n");
    exit(1);
  }
  if(strlen(argv[1]) >= MAXFILENAME) {
    printf("Filename, %s, is too long, cp to shorter name and try again\n",
        filename);
    exit(1);
  }
  strcpy(filename, argv[1]);
}

