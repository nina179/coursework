#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "grid.h"

/**
 * A class representing a shape.
 */
class Shape {
  public:
    virtual ~Shape() {
    }

    /**
     * Draws this shape on the provided grid.
     * @param grid The grid onto which to draw the shape.
     */
    virtual void draw(Grid* grid) = 0;
};
