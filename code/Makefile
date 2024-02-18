all: ../applications/main
	
../applications/main : code.o WBMP.o
	g++ code.o WBMP.o -o ../applications/main
code.o : code.cpp
	g++ -c code.cpp -o code.o
WBMP.o: WorkingWithBmpFiles.cpp
	g++ -c WorkingWithBmpFiles.cpp -o WBMP.o