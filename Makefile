CXX = clang++


SOURCES = $(wildcard **/*.cpp)
MAINS = $(patsubst %.cpp,%.out,$(SOURCES))

all: $(MAINS)


%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
