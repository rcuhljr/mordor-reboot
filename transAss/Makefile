CPPFLAGS=-g
CC=g++

all: testMData11

mdataTools.o: mdataTools.hpp mdataTools.cpp
	$(CC) $(CPPFLAGS) -c $^

mordorBinaryReader.o: mordorBinaryReader.hpp mordorBinaryReader.cpp
	$(CC) $(CPPFLAGS) -c $^

testMData11: mordorBinaryReader.o mdataTools.o readMData11.cpp
	$(CC) $^ -o testMData11

.PHONY : clean

clean:
	-rm *.o
	-rm *.gch
	-rm testMData11
