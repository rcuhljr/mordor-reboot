/*
 * Author Seabass
 * Purpose -- Read in a particular Mordor data file, MDATA11.MDR
 */

#include <iostream>
#include <fstream>
#include "mordorBinaryReader.hpp" // bring in the binary ready definitions
#include "mdataTools.hpp"         // constants, simple data file checks
#include "readMData11.hpp"

using namespace std;

static const int RECORD_SIZE = 20;


void printFieldRecord(fieldRecord *ret){
}

fieldRecord readFieldRecord(ifstream *mdata){
  fieldRecord ret;

  printFieldRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printCountHeader(countHeader *ret){
  cout << "Count: " << ret->count << endl;
}

countHeader readCountHeader(ifstream *mdata){
  countHeader ret;
  ret.count = readWord(mdata);
  printCountHeader(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printAreaRecord(areaRecord *ret){
  cout << "SpawnTypeMask: " << ret->spawnTypeMask << endl
       << "Lair ID: " << ret->lairID << endl;
}

areaRecord readAreaRecord(ifstream *mdata){
  areaRecord ret;

  printAreaRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printTeleporterRecord(teleporterRecord *ret){
  
}

teleporterRecord readTeleporterRecord(ifstream *mdata){
  teleporterRecord ret;

  printTeleporterRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printChuteRecord(chuteRecord *ret){
}

chuteRecord readChuteRecord(ifstream *mdata){
  chuteRecord ret;

  printChuteRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}


levelHeader readLevelHeader(ifstream *mdata_input){
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

void printLevelHeader(levelHeader *lh){
  cout << dec << "Width:\t\t" << lh->width << endl;
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

  if (not possiblyValidFile(datAbsolutePath, MDATA11)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA11.MDR" << endl;
    return 1;
  }

  ifstream mdata_input(datAbsolutePath, ios::binary | ios::in);
  cout << "Pointer at " << mdata_input.tellg() << endl;
  WORD numLevels = 0; 
  WORD recordNumber = 0;
  WORD levelOffset = 0;
  
  // documentation might be wrong, I think this is really a byte.
  numLevels = (WORD) readByte(&mdata_input);
  cout << dec << numLevels << " levels to read" << endl;

  for(int i = 0; i < numLevels; i++){
    cout << "Pointer at " << dec << mdata_input.tellg() << endl;
    recordNumber = (WORD) readWord(&mdata_input);
    levelOffset = readWord(&mdata_input);
    cout << dec << "Level " << i << " record " << recordNumber << 
      " starts at " << hex << levelOffset << endl;

    seekTo(&mdata_input, RECORD_SIZE);
  
  }
  levelHeader lh = readLevelHeader(&mdata_input);
  printLevelHeader(&lh);
  return 0;
}
