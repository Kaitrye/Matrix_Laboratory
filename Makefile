CC=clang++
CFLAGS=-c -pedantic-errors -gdwarf-4 -std=c++20
LDFLAGS=
SOURCES=matrixlab.cpp biginteger.cpp bigfraction.cpp formnodes.cpp functions.cpp matrix.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrixlab

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf *.o $(EXECUTABLE)
