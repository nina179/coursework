/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>

#include "horizontalLine.h"
#include "picture.h"
#include "point.h"
#include "rectangle.h"
#include "shape.h"
#include "shapeFactory.h"
#include "verticalLine.h"

using namespace std;

int readX() {
    int x;
    do {
        cout << "In what column?" << endl;
        cin >> x;
    } while (x < 0);
    return x;
}

int readY() {
    int y;
    do {
        cout << "In what row?" << endl;
        cin >> y;
    } while (y < 0);
    return y;
}

int readWidth() {
    int w;
    do {
        cout << "How wide?" << endl;
        cin >> w;
    } while (w < 0);
    return w;
}

int readHeight() {
    int h;
    do {
        cout << "How tall?" << endl;
        cin >> h;
    } while (h < 0);
    return h;
}

char readAppearance() {
    char c;
    cout << "What character should we use to draw it?" << endl;
    cin >> c;
    return c;
}

int readLength() {
    int l;
    do {
        cout << "How long should it be?" << endl;
        cin >> l;
    } while (l <= 0);
    return l;
}

int main() {
    Picture* picture = new Picture();

    cout << "Welcome to Artwork!" << endl << endl;

    bool quit = false;
    while (!quit) {
        cout << "What shape would you like to draw? (Or type 'quit' to quit.)" << endl;
        string shapeName;
        cin >> shapeName;
        Shape* newShape = nullptr;
        if (shapeName == "quit") {
            quit = true;
        } else if (shapeName == "point") {
            int x = readX();
            int y = readY();
            int c = readAppearance();
            newShape = createPoint(x, y, c);
        } else if (shapeName == "horizontalLine") {
            int x = readX();
            int y = readY();
            int l = readLength();
            int c = readAppearance();
            newShape = createHorizontalLine(x, y, l, c);
        } else if (shapeName == "verticalLine") {
            int x = readX();
            int y = readY();
            int l = readLength();
            int c = readAppearance();
            newShape = createVerticalLine(x, y, l, c);
        } else if (shapeName == "rectangle") {
            int x = readX();
            int y = readY();
            int w = readWidth();
            int h = readHeight();
            int c = readAppearance();
            newShape = createRectangle(x, y, w, h, c);
        } else {
            cout << "I don't recognize that shape name." << endl;
            cout << "Valid shape names are point, horizontalLine, "
                    "verticalLine, or "
                    "rectangle."
                 << endl;
        }
        if (newShape != nullptr) {
            picture->addShape(newShape);
        }
        cout << endl;
        cout << "Your artwork currently looks like this:" << endl << endl;
        picture->print();
    }

    cout << "Goodbye!" << endl;

    delete picture;

    return 0;
}
