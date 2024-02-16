all: main
main : code.o
	g++ code.o -o main
code.o : code.cpp
	g++ -c code.cpp -o code.o