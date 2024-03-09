# Configure compiler settings
CXX=clang++
CXXFLAGS=-gdwarf-4 -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the artwork program.
OFILES = \
	grid.o point.o horizontalLine.o verticalLine.o rectangle.o \
	shapeFactory.o picture.o
HFILES = \
	grid.h horizontalLine.h picture.h point.h rectangle.h shape.h \
	shapeFactory.h verticalLine.h
# UnitTest++ library needed for linking.
UNITTEST_LIB = -lUnitTest++

# This target builds everything.  It is the default.
all: artwork manualTests tests

# This target builds your artwork program.
artwork: $(OFILES) $(HFILES) shapeConstants.h artwork.o
	$(CXX) $(CXXFLAGS) $(OFILES) artwork.o -o artwork

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES) shapeConstants.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target does some behind-the-scenes work to figure out which shapes you
# have declared.
shapeConstants.h: $(HFILES)
	chmod +x .check_implementations.sh
	./.check_implementations.sh

# This target builds your tests.
tests: $(OFILES) $(HFILES) shapeConstants.h tests.cpp
	chmod +x .check_implementations.sh
	./.check_implementations.sh
	$(CXX) $(CXXFLAGS) $(UNITTEST_LIB) $(OFILES) tests.cpp -o tests

# This target builds your manual tests.
manualTests: $(OFILES) $(HFILES) shapeConstants.h manualTests.cpp
	$(CXX) $(CXXFLAGS) $(OFILES) manualTests.cpp -o manualTests

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f $(OFILES)
	rm -f artwork.o
	rm -f ./artwork
	rm -f ./tests
	rm -f ./manualTests
	rm -f ./shapeConstants.h
	rm -f test_output/*
