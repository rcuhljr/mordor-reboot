/*
 * Author Seabass
 * Purpose -- Common Utilities for MDATA validation
 */

#include <iostream>
#include <fstream>
#include "mdataTools.hpp"

using namespace std;

const int MDATA1 = 0;
const int MDATA2 = 1;
const int MDATA3 = 2;
const int MDATA5 = 3;
const int MDATA11 = 4;

const char* MDATA1_NAME = "MDATA1.MDR";
const char* MDATA2_NAME = "MDATA2.MDR";
const char* MDATA3_NAME = "MDATA3.MDR";
const char* MDATA5_NAME = "MDATA5.MDR";
const char* MDATA11_NAME = "MDATA11.MDR";

const int MDATA1_SIZE = -1; // size of MDATA11.MDR in bytes
const int MDATA2_SIZE = -1; // size of MDATA11.MDR in bytes
const int MDATA3_SIZE = -1; // size of MDATA11.MDR in bytes
const int MDATA5_SIZE = -1; // size of MDATA11.MDR in bytes
const int MDATA11_SIZE= -1; // size of MDATA11.MDR in bytes



const char* mdataFileName(int i){
  switch(i){
  case MDATA1:
    return MDATA1_NAME;
    break;
  case MDATA2:
    return MDATA2_NAME;
    break;
  case MDATA3:
    return MDATA3_NAME;
    break;
  case MDATA5:
    return MDATA5_NAME;
    break;
  case MDATA11:
    return MDATA11_NAME;
    break;
  default:
    cerr << "Unrecognized mdata const" << endl;
    break;
  }
  return 0; 
}

int mdataFileSize(int i){
  switch(i){
  case MDATA1:
    return MDATA1_SIZE;
    break;
  case MDATA2:
    return MDATA2_SIZE;
    break;
  case MDATA3:
    return MDATA3_SIZE;
    break;
  case MDATA5:
    return MDATA5_SIZE;
    break;
  case MDATA11:
    return MDATA11_SIZE;
    break;
  default:
    cerr << "Unrecognized mdata const" << endl;
    break;
  }
  return 0; 
}


bool validPath(char* path, const char* FNAME){
  int len = strlen(path);
  if(len < 11){ // MDATA11.MDR is 11 characters -- this must be wrong.
    return false;
  }else{
    int offset = len - 11;
    for(int i = 0; i < 11; i++){
      if(path[i+offset] != FNAME[i]){
        return false;
      }
    }
  }
  return true;
}


bool checkLength(ifstream *mdata_input, int SIZE){
  streampos start = mdata_input->tellg();
  mdata_input->seekg(0, ios::end);
  streampos end = mdata_input->tellg();
  int length = end - start;
  return (length == SIZE);
}


bool possiblyValidFile(char* path, int target){
  // is the given file valid -- just a quick test.  Exists, correct name, length
  if(not validPath(path, mdataFileName(target))){
    return false;
  }

  // pathname is ok -- carry on.
  ifstream mdata_input(path, ios::binary | ios::in);
  if (not mdata_input.good()){
    // file doesn't exist, quit.
    return false;
  }else if (not checkLength(&mdata_input, mdataFileSize(target))){
    return false;
  }
  //file exists, is of expected size, will be closed when destroyed.
  return true;
}
