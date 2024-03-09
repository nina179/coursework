/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "grid.h"
#include "horizontalLine.h"
#include "point.h"
#include "rectangle.h"
#include "shape.h"
#include "shapeConstants.h"
#include "picture.h"
#include "verticalLine.h"

using namespace std;

// TestGrid class
class TestGrid : public Grid {
public:
  TestGrid(int w, int h, char c) {
    this->width = w;
    this->height = h;
    this->backgroundSymbol = c;
    this->data = new char[this->width * this->height];
    for (int i = 0; i < this->width * this->height; i++) {
      this->data[i] = this->backgroundSymbol;
    }
  }
  ~TestGrid() {
    delete[] this->data;
  }
  void placeSymbol(int x, int y, char s) {
    this->data[x + y * this->width] = s;
  }
  std::string toString() {
    string s = "\n";
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            s += this->data[x + y * this->width];
            s += ' ';
        }
        s += '\n';
    }
    return s;
  }
  void print() {
    cout << this->toString();
  }
private:
  char* data;
  int width;
  int height;
  char backgroundSymbol;
};


#ifndef DECLARED_POINT
TEST(you_have_not_yet_declared_a_Point_class) {
    CHECK(false);
}
#endif //DECLARED_POINT
#ifndef DECLARED_HORIZONTALLINE
TEST(you_have_not_yet_declared_a_HorizontalLine_class) {
    CHECK(false);
}
#endif //DECLARED_HORIZONTALLINE
#ifndef DECLARED_VERTICALLINE
TEST(you_have_not_yet_declared_a_VerticalLine_class) {
    CHECK(false);
}
#endif //DECLARED_VERTICALLINE
#ifndef DECLARED_RECTANGLE
TEST(you_have_not_yet_declared_a_Rectangle_class) {
    CHECK(false);
}
#endif //DECLARED_RECTANGLE

#ifdef DECLARED_POINT
TEST(singlePoint) {
    Grid* grid = new TestGrid(3,3,'*');
    Point point(1,1,'@');
    point.draw(grid);
    CHECK_EQUAL("\n"
                "* * * \n"
                "* @ * \n"
                "* * * \n",
                grid->toString());
    delete grid;
}

TEST(manyPoints) {
    Grid* grid = new TestGrid(4,4,'*');
    Point point1(1,1,'@');
    Point point2(2,1,'@');
    Point point3(3,1,'@');
    Point point4(3,2,'#');
    Point point5(3,3,'#');
    point1.draw(grid);
    point2.draw(grid);
    point3.draw(grid);
    point4.draw(grid);
    point5.draw(grid);
    CHECK_EQUAL("\n"
                "* * * * \n"
                "* @ @ @ \n"
                "* * * # \n"
                "* * * # \n",
                grid->toString());
    delete grid;
}
#endif //DECLARED_POINT

#ifdef DECLARED_HORIZONTALLINE
TEST(singleLine) {
    Grid* grid = new TestGrid(5,5,'*');
    HorizontalLine line(1,0,4,'=');
    line.draw(grid);
    CHECK_EQUAL("\n"
                "* = = = = \n"
                "* * * * * \n"
                "* * * * * \n"
                "* * * * * \n"
                "* * * * * \n",
                grid->toString());
    delete grid;
}

#ifdef DECLARED_VERTICALLINE
TEST(manyLines) {
    Grid* grid = new TestGrid(8,8,'*');
    HorizontalLine line1(1,2,4,'=');
    HorizontalLine line2(2,6,5,'=');
    VerticalLine line3(4,0,8,'|');
    HorizontalLine line4(2,4,3,'=');
    line1.draw(grid);
    line2.draw(grid);
    line3.draw(grid);
    line4.draw(grid);
    CHECK_EQUAL("\n"
                "* * * * | * * * \n"
                "* * * * | * * * \n"
                "* = = = | * * * \n"
                "* * * * | * * * \n"
                "* * = = = * * * \n"
                "* * * * | * * * \n"
                "* * = = | = = * \n"
                "* * * * | * * * \n",
                grid->toString());
    delete grid;
}
#endif //DECLARED_VERTICALLINE
#endif //DECLARED_HORIZONTALLINE

#ifdef DECLARED_RECTANGLE
TEST(singleRectangle) {
    Grid* grid = new TestGrid(5,5,'*');
    Rectangle rect(1,0,3,4,'+');
    rect.draw(grid);
    CHECK_EQUAL("\n"
                "* + + + * \n"
                "* + + + * \n"
                "* + + + * \n"
                "* + + + * \n"
                "* * * * * \n",
                grid->toString());
    delete grid;
}

TEST(manyRectangles) {
    Grid* grid = new TestGrid(8,8,'*');
    Rectangle rect1(0,0,4,2,'1');
    Rectangle rect2(2,0,5,4,'2');
    Rectangle rect3(3,1,2,2,'3');
    rect1.draw(grid);
    rect2.draw(grid);
    rect3.draw(grid);
    CHECK_EQUAL("\n"
                "1 1 2 2 2 2 2 * \n"
                "1 1 2 3 3 2 2 * \n"
                "* * 2 3 3 2 2 * \n"
                "* * 2 2 2 2 2 * \n"
                "* * * * * * * * \n"
                "* * * * * * * * \n"
                "* * * * * * * * \n"
                "* * * * * * * * \n",
                grid->toString());
    delete grid;
}

TEST(pictureWithThreeRectangles) {
    Shape* myShape1 = new Rectangle(0, 0, 7, 7, '$');
    Shape* myShape2 = new Rectangle(1, 1, 6, 4, '-');
    Shape* myShape3 = new Rectangle(3, 2, 4, 3, '&');
    Picture myPicture;
    myPicture.addShape(myShape1);
    myPicture.addShape(myShape2);
    myPicture.addShape(myShape3);
    CHECK_EQUAL("\n"
                "$ $ $ $ $ $ $ * * * * * * * * * * * * * \n"
                "$ - - - - - - * * * * * * * * * * * * * \n"
                "$ - - & & & & * * * * * * * * * * * * * \n"
                "$ - - & & & & * * * * * * * * * * * * * \n"
                "$ - - & & & & * * * * * * * * * * * * * \n"
                "$ $ $ $ $ $ $ * * * * * * * * * * * * * \n"
                "$ $ $ $ $ $ $ * * * * * * * * * * * * * \n"
                "* * * * * * * * * * * * * * * * * * * * \n"
                "* * * * * * * * * * * * * * * * * * * * \n"
                "* * * * * * * * * * * * * * * * * * * * \n",
                "\n" + myPicture.toString());
}
#endif //DECLARED_RECTANGLE

int main() {
    return UnitTest::RunAllTests();
}
