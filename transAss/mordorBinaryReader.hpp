#ifndef MORDOR_BIN_READER
#define MORDOR_BIN_READER

#include <fstream>
using namespace std;

typedef unsigned char BYTE;  // 1 byte
typedef unsigned short WORD; // 2 bytes wide
typedef unsigned long DWORD; // 4 bytes, or long word
typedef float CURRENCY;

BYTE readByte(ifstream *mdata_input);
WORD readWord(ifstream *mdata_input);
DWORD readDWord(ifstream *mdata_input);
CURRENCY readCurrency(ifstream *mdata_input);
char* readVBString(ifstream *mdata_input);

#endif
