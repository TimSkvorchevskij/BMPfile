CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=code.cpp BMPfile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../applications/main.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS)