# Configure compiler settings
CXX=clang++
CXXFLAGS=-gdwarf-4 -std=c++11 -Werror

# The object files for the program.
OFILES = quickSort.o

# UnitTest++ library needed for linking.
UNITTEST_LIB = -lUnitTest++

# A special target to build everything
all: sortArgs tests

# This target builds your main program.
sortArgs: $(OFILES) sortArgs.o
	$(CXX) $(CXXFLAGS) -o $@ $^
# This target builds your tests.
tests: tests.o $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(UNITTEST_LIB)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean all
# This target deletes the temporary files we have built.
clean:
	rm -f *.o
	rm -f sortArgs
	rm -f tests
	rm -f *.aux *.log *.fls *.*_latexmk *.synctex.gz
	rm -f LearningLaTeX.pdf
