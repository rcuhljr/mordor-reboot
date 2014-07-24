/* 
 *  Tool for reading the binary data file formats of mordor
 */


#include <fstream>
#include "mordorBinaryReader.hpp"

using namespace std;




BYTE readByte(ifstream *mdata_input){
  static char *buff = new char[1];
  mdata_input->read(buff,1);
  BYTE ret = (BYTE) *buff;
  free(buff);
  return ret;
}


WORD readWord(ifstream *mdata_input){
  static char *buff = new char[2];
  mdata_input->read(buff, 2);
  WORD ret = (WORD) *buff;
  free(buff);
  return (WORD) *buff;
}

DWORD readDWord(ifstream *mdata_input){
  static char *buff = new char[4];
  mdata_input->read(buff, 4);
  DWORD ret = (DWORD) *buff;
  free(buff);
  return ret;
}

CURRENCY readCurrency(ifstream *mdata_input){
  static char *buff = new char[8];
  mdata_input->read(buff,8);
  CURRENCY ret = (CURRENCY) *buff;
  free(buff);
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
  return ret;
}
