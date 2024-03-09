/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "cpipe.h"
#include "guiFailure.h"

cpipe::cpipe() {
    if (pipe(fd) != 0) {
        throw GuiFailure("Failed to create pipe");
    }
}

cpipe::~cpipe() {
    this->close();
}

const int cpipe::read_fd() const {
    return fd[0];
}

const int cpipe::write_fd() const {
    return fd[1];
}

void cpipe::close() {
    ::close(fd[0]);
    ::close(fd[1]);
}
