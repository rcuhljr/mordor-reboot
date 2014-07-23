/*
 * Author Seabass
 * Purpose -- Read in a particular Mordor data file, MDATA11.MDR
 */

#include <iostream>
#include <fstream>
using namespace std;

static const string FNAME = "MDATA11.MDR";
static const int SIZE = 339606; // size of MDATA11.MDR in bytes

struct levelHeader {
  unsigned short width;
  unsigned short height;
  unsigned short levelNumber;
  unsigned short numAreas;
  unsigned short numChutes;
  unsigned short numTeleports;
};

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

static bool possiblyValidFile(char* path){
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
  //file exists, is of expected size, will be closed when destroyed.
  return true;
}

static unsigned short readWord(ifstream *mdata_input){
  static char* buff = new char[2];
  mdata_input->read(buff, 2);
  return (unsigned short) *buff;
}

static levelHeader readLevelHeader(ifstream *mdata_input){
  // width       -- word
  // height      -- word
  // level #     -- word
  // # areas     -- word
  // # chutes    -- word
  // # teleports -- word

  levelHeader thisLevel;

  thisLevel.width = readWord(mdata_input);
  thisLevel.height = readWord(mdata_input);
  thisLevel.levelNumber = readWord(mdata_input);
  thisLevel.numAreas = readWord(mdata_input);
  thisLevel.numChutes = readWord(mdata_input);
  thisLevel.numTeleports = readWord(mdata_input);
  return thisLevel;
}

static void printLevelHeader(levelHeader *lh){
  cout << "Width:\t\t" << lh->width << endl;
  cout << "Height:\t\t" << lh->height << endl;
  cout << "Level:\t\t" << lh->levelNumber << endl;
  cout << "Areas:\t\t" << lh->numAreas << endl;
  cout << "Chutes:\t\t" << lh->numChutes << endl;
  cout << "Teleports:\t" << lh->numTeleports << endl;
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

  possiblyValidFile(datAbsolutePath);

  ifstream mdata_input(datAbsolutePath, ios::binary | ios::in);
  levelHeader lh = readLevelHeader(&mdata_input);
  unsigned short numLevels = readWord(&mdata_input);
  unsigned short levelOffset = 20;

  cout << numLevels << " levels to read" << endl;

  for(int i = 1; i < numLevels; i++){
    levelOffset = readWord(&mdata_input);
    cout << "Level " << i << " starts at " << levelOffset << endl;
  }
  printLevelHeader(&lh);
  return 0;
}
