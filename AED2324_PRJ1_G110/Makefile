# Set g++ as the C++ compiler
CXX = g++

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES = code/Data.cpp code/ReadData.cpp code/UtilityFunctions.cpp code/Consult.cpp code/Script.cpp code/Change.cpp

# Your target program
PROGRAMS = run

# Doxygen configuration file
DOXYGEN_CONFIG = docs/Doxyfile

# Target directory for Doxygen documentation
DOXYGEN_OUTPUT_DIR = docs/output

# Target for Doxygen documentation
DOXYGEN_TARGET = $(DOXYGEN_OUTPUT_DIR)/html/index.html

all: $(PROGRAMS)

run: $(COMMON_CPP_FILES) code/runscript.cpp
	$(CXX) -o run code/runscript.cpp $(COMMON_CPP_FILES)

doxygen: $(DOXYGEN_CONFIG)
	doxygen $<

clean:
	rm -fr *.dSYM $(PROGRAMS)

.PHONY: doxygen
