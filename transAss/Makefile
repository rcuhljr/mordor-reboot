CPPFLAGS=-g
CC=g++


all: test

*.o: *.hpp *.cpp
	$(CC) $(CPPFLAGS) -c $^

testMData11: mordorBinaryReader.o mdataTools.o readMData11.o
	$(CC) $(CPPFLGAS) $^ -o $@

testMData1: mordorBinaryReader.o mdataTools.o readMData1.o
	$(CC) $^ -o $@

testMData2: mordorBinaryReader.o mdataTools.o readMData2.o
	$(CC) $^ -o $@

testMData3: mordorBinaryReader.o mdataTools.o readMData3.o
	$(CC) $^ -o $@

testMData5: mordorBinaryReader.o mdataTools.o readMData5.o
	$(CC) $^ -o $@

test: testMData1 testMData2 testMData3 testMData5 testMData11

.PHONY : clean

clean:
	-rm *.o
	-rm *.gch
	-rm testMData1
	-rm testMData2
	-rm testMData3
	-rm testMData5
	-rm testMData11
