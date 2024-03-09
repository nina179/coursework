/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms

  This program grabs the index of desired pixel and performs transformations on .ppm files
*/

#include "image.h"

#include <iostream>
using namespace std;

// Note: see image.h for documentation on functions.

int pixelToIndex(int width, int x, int y) {
  // TODO: implement this function correctly
  int row_length = 3*width;
  int row_start = 3*width*y;
  int pixel = row_start + 3*x;

  // returns index of the first integer in the specified pixel
  return pixel; 
}

void noRed(int width, int height, int* ppm) {
  // loops over every value of y    
  for (int y=0; y<height; y++) {
    // loops over every value of x
    for (int x=0; x<width; x++) {
      // finds index of r value in ppm[] and sets it to 0
      int i = pixelToIndex(width, x, y);
      ppm[i] = 0;
    }
  }
}

void noGreen (int width, int height, int* ppm) {
  // loops over every value of y    
  for (int y=0; y<height; y++) {
    // loops over every value of x
    for (int x=0; x<width; x++) {
      // finds index of b value in ppm[] and sets it to 0
      int i = pixelToIndex(width, x, y);
      ppm[i+1] = 0;
    }
  }
}

void noBlue (int width, int height, int* ppm) {
  // loops over every value of y    
  for (int y=0; y<height; y++) {
    // loops over every value of x
    for (int x=0; x<width; x++) {
      // finds index of g value in ppm[] and sets it to 0
      int i = pixelToIndex(width, x, y);
      ppm[i+2] = 0;
    }
  }
}

void invert (int width, int height, int* ppm) {
  // finds total number of pixels
  int total = 3*width*height;

  // loops over every value in ppm[] and subtracts it from 255    
  for (int i=0; i<total; i++) {
    ppm[i] = 255 - ppm[i];
  }
}

void grayscale (int width, int height, int* ppm) {
  // loops over every value of y    
  for (int y=0; y<height; y++) {
    // loops over every value of x
    for (int x=0; x<width; x++) {      
      int i = width-x-1;
      int r = pixelToIndex(width, x, y);
      int b = r + 1;
      int g = b + 1;

      // averages the rbg values
      int red = ppm[r];
      int blue = ppm[b];
      int green = ppm[g];
      int avg = (red + blue + green)/3;

      // sets each rbg value in given pixel to avg
      ppm[r] = avg;
      ppm[b] = avg;
      ppm[g] = avg;
    }
  }
}

void flipHorizontally (int width, int height, int* ppm) {
  for (int y=0; y<height; y++) {
    for (int x=0; x<(width/2); x++) {
      // find rbg values of each pixel
      for (int i=0; i<3; i++) {
        // saves index of first and last rbg values in the row
        int fp = pixelToIndex(width, x, y) + i;
        int lp = pixelToIndex(width, width-x-1, y) + i;

        // swaps first and last rbg values in the row
        int temp = ppm[fp];
        ppm[fp] = ppm[lp];
        ppm[lp] = temp;
      }
    }
  }
}

void flipVertically (int width, int height, int* ppm) {
  for (int x=0; x<width; x++) {
    for (int y=0; y<(height/2); y++) {
      // finds rbg values of leftmost pixel on column x
      int r_left = pixelToIndex(width, x, y);
      int b_left = r_left + 1;
      int g_left = b_left + 1;

      // finds index of rightmost pixel on column x
      int i = height-y-1;

      // finds rbg values of rightmost pixel on column x
      int r_right = pixelToIndex(width, x, i);
      int b_right = r_right + 1;
      int g_right = b_right + 1;   

      // swaps pixels
      int r_temp = ppm[r_left];
      ppm[r_left] = ppm[r_right];
      ppm[r_right] = r_temp;

      int b_temp = ppm[b_left];
      ppm[b_left] = ppm[b_right];
      ppm[b_right] = b_temp;

      int g_temp = ppm[g_left];
      ppm[g_left] = ppm[g_right];
      ppm[g_right] = g_temp;
    }
  }
}
