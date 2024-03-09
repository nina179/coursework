#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

using std::string;

/**
 * Determines the width (number of columns) in a PPM P3 file.
 * @param filename The pathname of the file.
 * @return The width of the image in that file.
 */
int ppm_width(string filename);

/**
 * Determines the height (number of rows) in a PPM P3 file.
 * @param filename The pathname of the file.
 * @return The height of the image in that file.
 */
int ppm_height(string filename);

/**
 * Reads a PPM file.  This file must in PPM P3 format.
 * @param filename The pathname of the file to read.
 * @return The array containing the PPM pixels.
 */
int* read_ppm(string filename);

/**
 * Writes a PPM file.  The provided array is assumed to contain red, green, and
 * blue pixel samples in the range of 0 to 255.
 * @param filename The name of the file to write.
 * @param width The width of the image data.
 * @param height The height of the image data.
 * @param ppm The PPM image contents to write.
 */
void write_ppm(string filename, int width, int height, int* ppm);
