CPPFLAGS=-g
CC=g++

all: testMData11

mordorBinaryReader.o: mordorBinaryReader.hpp mordorBinaryReader.cpp
	$(CC) $(CPPFLAGS) -c $^

testMData11: mordorBinaryReader.o readMData11.cpp
	$(CC) $^ -o testMData11

.PHONY : clean

clean:
	-rm *.o
	-rm *.gch
	-rm testMData11
