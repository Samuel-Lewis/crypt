# Compilation
CXX = g++
INCLUDES =-I ./libs/lunchbox/include
CXXFLAGS =$(INCLUDES) -std=c++11 -pedantic -Wall -Wextra -O2
LIBS = -lncurses


# Sources and file names
SOURCES = $(shell find . -type f -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)
EXE = Crypt
all: $(EXE)

# Object Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Final compilation and output
$(EXE): $(OBJECTS) 
	$(CXX) $(OBJECTS) $(LIBS) -o $(EXE)

# Clean all objects files and exe.
clean:
	rm -f $(OBJECTS) $(EXE)
