CXX= g++ --std=c++11
CXXFLAGS= -g -Wall

all:  floorplan bst avlbst

bst: bst.o
	$(CXX) $(CXXFLAGS) -o $@ bst.o

bst.o: bst.h avlbst.h bst.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c bst.cpp

avlbst: avlbst.o
	$(CXX) $(CXXFLAGS) -o $@ avlbst.o

avlbst.o: bst.h avlbst.h avlbst.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c avlbst.cpp

floorplan: floorplan.cpp avlbst.h bst.h
	$(CXX) $(CXXFLAGS) floorplan.cpp -o $@

clean:
	rm -f *.o bst
	rm -f *.o floorplan
