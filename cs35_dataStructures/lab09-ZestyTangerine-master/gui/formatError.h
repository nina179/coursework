/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include "guiFailure.h"

class FormatError : public GuiFailure {
  public:
    explicit FormatError(const char* message) : GuiFailure(message) {
    }
    explicit FormatError(std::string& message) : GuiFailure(message) {
    }
    virtual ~FormatError() throw() {
    }
};
