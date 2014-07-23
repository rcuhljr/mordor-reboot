/*
 * Author Seabass
 * Purpose -- Read in a particular Mordor data file, MDATA11.MDR
 */

#include <iostream>
#include <fstream>
using namespace std;

static const string FNAME = "MDATA11.MDR";
static const int SIZE = 339606; // size of MDATA11.MDR in bytes

static bool validPath(char* path){
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

static bool checkLength(ifstream *mdata_input){
  streampos start = mdata_input->tellg();
  mdata_input->seekg(0, ios::end);
  streampos end = mdata_input->tellg();
  int length = end - start;
  return (length == SIZE);
}

static bool validFile(char* path){
  // is the given file valid -- just a quick test.  Exists, correct name, length

  if(not validPath(path)){
    return false;
  }

  // pathname is ok -- carry on.
  ifstream mdata_input(path, ios::binary | ios::in);
  if (not mdata_input.good()){
    // file doesn't exist, quit.
    return false;
  }else if (not checkLength(&mdata_input)){
    return false;
  }
  //file exists, is of expected size

  return true;
}

// testing main point -- this won't be compiled on it's own
int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << "Expected exactly one argument -- the absolute path to the MDAT11.MDR" << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  validFile(datAbsolutePath);

  return 0;
}
