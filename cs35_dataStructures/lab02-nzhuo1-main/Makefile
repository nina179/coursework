# Configure compiler settings
SHARED = /home/soni/public/cs35/picfilter/
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the picfilter program.
OFILES = ppmio.o image.o

# This target builds your picfilter program.
picfilter: $(OFILES) picfilter.o protect_test_data
	$(CXX) $(CXXFLAGS) -o $@ picfilter.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target runs the automated tests.
tests: picfilter 
	chmod +x testFilters.sh
	./testFilters.sh

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f $(OFILES)
	rm -f picfilter.o
	rm -f ./picfilter
	rm -f test_output/*

# This target is intended to prevent accidental modification of the provided
# test data files.
.PHONY: protect_test_data
protect_test_data:
	chmod -R -w test_data
