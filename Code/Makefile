# Set g++ as the C++ compiler
CXX=g++

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES=Data.cpp ReadData.cpp UtilityFunctions.cpp Consult.cpp Script.cpp Change.cpp

# Your target program
PROGRAMS=run

all: $(PROGRAMS)

run: $(COMMON_CPP_FILES) runscript.cpp
	$(CXX) -o run runscript.cpp $(COMMON_CPP_FILES)

# Doxygen documentation target
doxygen:
	doxygen Doxyfile

clean:
	rm -fr *.dSYM $(PROGRAMS)

.PHONY: doxygen