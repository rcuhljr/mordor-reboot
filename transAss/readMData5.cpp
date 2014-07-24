
#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "readMData5.hpp"

using namespace std;


int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << "Expected exactly one argument -- the absolute path to the MDATA5.MDR" << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (not possiblyValidFile(datAbsolutePath, MDATA5)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA5.MDR" << endl;
    return 1;
  }

  return 0;
}
