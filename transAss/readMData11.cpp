/*
 * Author Seabass
 * Purpose -- Read in a particular Mordor data file, MDATA11.MDR
 */

#include <iostream>
#include <fstream>
#include "mordorBinaryReader.hpp" // bring in the binary ready definitions
#include "mdataTools.hpp"         // constants, simple data file checks

using namespace std;


static const int RECORD_SIZE = 20;

struct levelHeader {
  unsigned short width;
  unsigned short height;
  unsigned short levelNumber;
  unsigned short numAreas;
  unsigned short numChutes;
  unsigned short numTeleports;
};

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

  possiblyValidFile(datAbsolutePath, MDATA11);

  ifstream mdata_input(datAbsolutePath, ios::binary | ios::in);

  unsigned short numLevels = readWord(&mdata_input);
  unsigned short levelOffset = 0;

  cout << numLevels << " levels to read" << endl;

  for(int i = 1; i < numLevels; i++){
    levelOffset = readWord(&mdata_input);
    cout << "Level " << i << " starts at " << levelOffset << endl;
  }
  levelHeader lh = readLevelHeader(&mdata_input);
  printLevelHeader(&lh);
  return 0;
}
