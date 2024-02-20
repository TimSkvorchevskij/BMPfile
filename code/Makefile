CC=g++
CFLAGS=-c -pedantic-errors -g -std=c++17
LDFLAGS=
SOURCES=code.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../applications/main

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS)