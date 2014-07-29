/* 
 *  Tool for reading the binary data file formats of mordor
 */


#include <fstream>
#include "mordorBinaryReader.hpp"

using namespace std;


int point = 0;

BYTE readByte(ifstream *mdata_input){
  static char *buff = new char[1];
  mdata_input->read(buff,1);
  BYTE ret = (BYTE) *buff;
  point++;
  return ret;
}


WORD readWord(ifstream *mdata_input){
  static char *buff = new char[2];
  mdata_input->read(buff, 2);  
  WORD ret = (WORD) *buff;
  point += 2;
  return ret;
}

SWORD readSWord(ifstream *mdata_input){
  static char *buff = new char[2];
  mdata_input->read(buff, 2);  
  SWORD ret = (SWORD) *buff;
  point += 2;
  return ret;
}

DWORD readDWord(ifstream *mdata_input){
  static char *buff = new char[4];
  mdata_input->read(buff, 4);
  DWORD ret = (DWORD) *buff;
  point += 4;
  return ret;
}

CURRENCY readCurrency(ifstream *mdata_input){
  static char *buff = new char[8];
  mdata_input->read(buff,8);
  CURRENCY ret = (CURRENCY) *buff;
  point += 8;
  return ret;
}

int readInt(ifstream *mdata_input){
  static char* buff = new char[4]; // 4 bytes, 32 bits
  mdata_input->read(buff, 4);
  point += 4;
  int ret = (int) *buff;
  return ret;
}

char* readVBString(ifstream *mdata_input){
  // allocates and returns a string.
  int length = readWord(mdata_input);
  char *ret = new char[length+1];
  mdata_input->read(ret,length);
  // Note that I only suspect that the string isn't properly null
  // terminated, I should check on that. - JTT
  ret[length] = '\0';
  point += length;
  return ret;
}

char* seekTo(ifstream *mdata_input, int goal){
  int length = goal - point;

  if(length < 0 ){   // already too far!
    return 0;
  }

  char *discard = new char[length];
  mdata_input->read(discard, length);

  //reset point
  point = 0;
  return discard;
}

void printLoc(ifstream *mdata_input, int offset, const char *prefix){
  cout << prefix << "\t\t";
  cout << hex << "Position: 0x" << point - offset << "\t\t\t";
  cout << hex << "Memory Offset: 0x" << mdata_input->tellg()<< endl;
}


bool checkAlignment(ifstream *mdata_input){
  WORD isZero = 42;
  isZero = readWord(mdata_input);
  return isZero == 0;
}
