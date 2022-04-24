CXX = g++
CXXFLAGS = -std=c++11 -c -g -Wall
OBJS = main.o problem.o node.o solver.o
PROG = puzzle

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(OBJS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

problem.o: problem.cpp problem.hpp
	$(CXX) $(CXXFLAGS) problem.cpp

node.o: node.cpp node.hpp
	$(CXX) $(CXXFLAGS) node.cpp

solver.o: solver.cpp solver.hpp
	$(CXX) $(CXXFLAGS) solver.cpp

clean:
	rm $(PROG) $(OBJS)

