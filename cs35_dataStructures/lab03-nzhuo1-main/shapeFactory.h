#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "shape.h"

/**
 * Creates a point shape with the provided arguments.
 * @param x The X coordinate of the point.
 * @param y The Y coordinate of the point.
 * @param appearance The character used to represent the point.
 * @return A pointer to the new point.  The caller assumes ownership of this
 *         object.
 */
Shape* createPoint(int x, int y, char appearance);

/**
 * Creates a horizontal line shape with the provided arguments.
 * @param x The leftmost X coordinate of the line.
 * @param y The Y coordinate of the line.
 * @param length The length of the line in grid squares.
 * @param appearance The character used to draw the line.
 * @return A pointer to the new line.  The caller assumes ownership of this
 *         object.
 */
Shape* createHorizontalLine(int x, int y, int length, char appearance);

/**
 * Creates a vertical line shape with the provided arguments.
 * @param x The X coordinate of the line.
 * @param y The topmost Y coordinate of the line.
 * @param length The length of the line in grid squares.
 * @param appearance The character used to draw the line
 * @return A pointer to the new line.  Caller assumes ownership of this
 *         object.
 */
Shape* createVerticalLine(int x, int y, int length, char appearance);

/**
 * Creates a rectangle shape with the provided arguments.
 * @param x The X coordinate of the upper left corner of the rectangle.
 * @param y The Y coordinate of the upper left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param appearance The character used to draw the rectangle.
 * @return A pointer to the new rectangle. Caller assumes ownership of this
 *         object.
 */
Shape* createRectangle(int x, int y, int width, int height, char appearance);
