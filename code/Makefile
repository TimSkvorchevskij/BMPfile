all: ../applications/main
	
../applications/main : code.o
	g++ code.o -o ../applications/main
code.o : code.cpp
	g++ -c code.cpp -o code.o