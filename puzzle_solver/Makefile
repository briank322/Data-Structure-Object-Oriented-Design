CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=board.o puzzle_heur.o puzzle_move.o puzzle_solver.o puzzle.o

all: puzzle heap

heap: heap.h heaptest.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ heap.h heaptest.cpp

puzzle: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

board.o: board.h board.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp

puzzle_heur.o: puzzle_heur.h puzzle_heur.cpp board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp

puzzle_move.o: puzzle_move.h puzzle_move.cpp board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp

puzzle_solver.o: puzzle_solver.h puzzle_solver.cpp board.h \
	puzzle_move.h puzzle_heur.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp

puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_move.h puzzle_solver.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp
clean:
	rm -f *.o puzzle
	
