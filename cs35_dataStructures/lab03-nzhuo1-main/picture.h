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
 * A class representing pictures composed of a number of shapes.
 */
class Picture {
public:
    /**
     * Creates a new, empty picture.
     */
    Picture();

    /**
     * Cleans up the resources used by a picture.
     */
    ~Picture();

    /**
     * Converts a picture to a string.  This Picture uses a Grid to
     * draw all of its Shapes; the returned string is the string from
     * that Grid.  @return A string representing the appearance of
     * this Picture.
     */
    std::string toString();

    /**
     * Prints a picture.  This routine displays the contents of the
     * picture to standard output in a 40x10 grid (the width is double
     * the defined width of 20 becauses spaces are interspersed).
     */
    void print();

    /**
     * Adds a shape to a picture.  The new shape is placed above the other
     * shapes in the picture.  Ownership of the shape is transferred to this
     * object.
     * @param shape The shape to add to this picture.
     */
    void addShape(Shape* shape);

private:
    /** The number of shapes currently appearing in this picture. */
    int numberOfShapes;
    /** The array containing the pointers to shapes in this picture. */
    Shape** shapes;
};
