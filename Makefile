CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -pedantic
BIN=ChocAn

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^
	mkdir members
	mkdir providers

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm -rf members
	rm -rf providers
	rm $(BIN)
