CXX = clang++
CXXFLAGS = --std=c++11


SOURCES = $(wildcard **/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
MAINS = $(patsubst %.cpp,%.out,$(wildcard **/*main.cpp))

$(MAINS): $(OBJECTS)

all: $(OBJECTS) $(MAINS)

clean:
	rm $(OBJECTS) $(MAINS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.out: %.o
	$(CXX) $(CXXFLAGS) $< -o $@
