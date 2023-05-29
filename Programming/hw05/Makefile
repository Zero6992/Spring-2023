CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS =
SOURCES = hw05.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
