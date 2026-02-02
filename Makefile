CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

all: testbst

testbst: testbst.o intbst.o
	$(CXX) $(CXXFLAGS) testbst.o intbst.o -o testbst

testbst.o: testbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c testbst.cpp

intbst.o: intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c intbst.cpp

clean:
	rm -f *.o testbst
