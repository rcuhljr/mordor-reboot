#ifndef MORDOR_BIN_READER
#define MORDOR_BIN_READER

#include <fstream>
#include <iostream>
using namespace std;


typedef unsigned char BYTE;  // 1 byte
typedef unsigned short WORD; // 2 bytes wide
typedef signed short SWORD;
typedef unsigned long DWORD; // 4 bytes, or long word
typedef float CURRENCY;

void printLoc(ifstream *mdata, int offset, const char *prefix);
BYTE readByte(ifstream *mdata_input);
WORD readWord(ifstream *mdata_input);
SWORD readSWord(ifstream *mdata_input);
DWORD readDWord(ifstream *mdata_input);
int readInt(ifstream *mdata_input);
CURRENCY readCurrency(ifstream *mdata_input);
char* readVBString(ifstream *mdata_input);
char* seekTo(ifstream *mdata_input, int goal);
bool checkAlignment(ifstream *mdata_input);

#endif
