/* 
 *  Tool for reading the binary data file formats of mordor
 */

#include <fstream>
#include "mordorBinaryReader.hpp"

using namespace std;


int point = 0;

BYTE readByte(ifstream *mdata_input){
  char buff[1] = {0};
  mdata_input->read(buff,sizeof(buff));
  BYTE ret = (BYTE) *buff;
  point += sizeof(buff);
  return ret;
}


WORD readWord(ifstream *mdata_input){
  unsigned char buff[2] = {0,0};
  mdata_input->read((char*) buff, sizeof(buff));  
  WORD ret = (WORD) (buff[1] << 8 | buff[0]);
  point += sizeof(buff);
  return ret;
}

WORD readWordByteOrder(ifstream *mdata_input){
  unsigned char buff[2] = {0,0};
  mdata_input->read((char*) buff, sizeof(buff));  
  WORD ret = (WORD) (buff[0] << 8 | buff[1]);
  point += sizeof(buff);
  return ret;
}

SWORD readSWord(ifstream *mdata_input){
  char buff[2] = {0,0};
  mdata_input->read(buff, sizeof(buff));  
  SWORD ret = (SWORD) (buff[0] << 8 | buff[1]);
  point += sizeof(buff);
  return ret;
}

DWORD readDWord(ifstream *mdata_input){
  char buff[4] = {0,0,0,0};
  mdata_input->read(buff, sizeof(buff));
  DWORD ret = (DWORD) *buff;
  point += sizeof(buff);
  return ret;
}

CURRENCY readCurrency(ifstream *mdata_input){
  char buff[8] = {0,0,0,0,0,0,0,0};
  mdata_input->read(buff, sizeof(buff));
  CURRENCY ret = (CURRENCY) *buff;
  point += sizeof(buff);
  return ret;
}

int readInt(ifstream *mdata_input){
  char buff[4] = {0,0,0,0};
  mdata_input->read(buff, sizeof(buff));
  point += sizeof(buff);
  int ret = (int) *buff;
  return ret;
}

char* readVBString(ifstream *mdata_input){
  // allocates and returns a string.
  int length = readWord(mdata_input);
  char *ret = new char[length + 1]; //and one for \0
  mdata_input->read(ret,length);
  ret[length] = '\0'; //make it a proper C-string
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
  WORD isZero = readWord(mdata_input);
  return isZero == 0;
}

bool checkByteAlignment(ifstream *mdata_input){
  BYTE isZero = readByte(mdata_input);
  return isZero == 0;
}
