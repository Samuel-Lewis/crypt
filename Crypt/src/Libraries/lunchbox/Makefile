# MAKE SURE TO RENAME TO 'Makefile' BEFORE ATTEMPTING TO MAKE

# Compilation
CXX =g++
INCLUDES =#-I ./lunchbox/include
CXXFLAGS =$(INCLUDES) -pedantic -Wall -Wextra -O2 -std=c++11# -g
LIBS =
DEFS =

# Sources and file names
SOURCES =$(shell find . -type f -name "*.cpp")
OBJECTS =$(SOURCES:.cpp=.o)
OUTDIR =./
EXE =main.out
all: $(OUTDIR)/$(EXE)

example: DEFS += -D_LB_EXAMPLE
example: all

# Object Compilation
$(OUTDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -c $^ -o $@

# Final compilation and output
$(EXE): $(OBJECTS) 
	$(CXX) $(OBJECTS) $(LIBS) -o $(EXE)

# Clean all objects files and exe.
clean:
	rm -f $(OBJECTS) $(EXE)

