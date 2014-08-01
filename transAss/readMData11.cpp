/*
 * Author Seabass
 * Purpose -- Read in a particular Mordor data file, MDATA11.MDR
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "mordorBinaryReader.hpp" // bring in the binary ready definitions
#include "mdataTools.hpp"         // constants, simple data file checks
#include "readMData11.hpp"
#include "assert.h"

using namespace std;

static const int RECORD_SIZE = 20;
static const int MAX_WIDTH = 30;
static const int MAX_HEIGHT = 30;


void printFieldRecord(fieldRecord *ret){
  cout << "Spawn Area ID: " << ret->spawnAreaID << endl
       << "Mask: " << ret->fieldMask << endl;
}

fieldRecord readFieldRecord(ifstream *mdata){
  fieldRecord ret;
  ret.spawnAreaID = readWord(mdata);

  for(int i = 0; i < 8; i++){
    ret.fieldMask[i] = readByte(mdata);
  }

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

countHeader readOffsetHeader(ifstream *mdata){
  countHeader ret;
  // I actually want the offset to reflect the physical location in the file.
  WORD read = readWord(mdata);
  cout << "Read: " << showbase << internal << setfill('0') << hex << read << dec << endl;
  ret.count = RECORD_SIZE * (read - 1); // -1 taken from wabbits editor
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
  ret.spawnTypeMask = readDWord(mdata);
  ret.lairID = readWord(mdata);
  printAreaRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printTeleporterRecord(teleporterRecord *ret){
  cout << "X: " << ret->srcX << "\tY: " << ret->srcY << endl
       << "X': " << ret->destX << "\tY': " << ret->destY << endl
       << "Z: " << ret-> destZ << endl;
}

teleporterRecord readTeleporterRecord(ifstream *mdata){
  teleporterRecord ret;
  ret.srcX = readWord(mdata);
  ret.srcY = readWord(mdata);
  ret.destX = readWord(mdata);
  ret.destY = readWord(mdata);
  ret.destZ = readWord(mdata);
  printTeleporterRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printChuteRecord(chuteRecord *ret){
  cout << "X: " << ret->x << "\tY: " << ret->y << "\tZ: " << ret->dropDepth << endl;
}

chuteRecord readChuteRecord(ifstream *mdata){
  chuteRecord ret;
  ret.x = readWord(mdata);
  ret.y = readWord(mdata);
  ret.dropDepth = readWord(mdata);
  printChuteRecord(&ret);
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printLevelHeader(levelHeader *lh){
  cout << dec << "Width:\t\t" << lh->width << endl;
  cout << "Height:\t\t" << lh->height << endl;
  cout << "Level:\t\t" << lh->levelNumber << endl;
  cout << "Areas:\t\t" << lh->numAreas << endl;
  cout << "Chutes:\t\t" << lh->numChutes << endl;
  cout << "Teleports:\t" << lh->numTeleports << endl;
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

  printLevelHeader(&thisLevel);
  seekTo(mdata_input, RECORD_SIZE);
  return thisLevel;
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
  countHeader numberOfLevels = readCountHeader(&mdata_input);
  countHeader levelOffsets[numberOfLevels.count];
  levelHeader levelHeaders[numberOfLevels.count];

  cout << "Num levels: " << numberOfLevels.count << endl;

  // read in the level offsets
  for(int i = 0; i < numberOfLevels.count; i++){
    cout << "Pointer at: " << mdata_input.tellg() << endl;
    cout << "Level " << i << "\tOffset: ";
    levelOffsets[i] = readOffsetHeader(&mdata_input);
  }

  // try to read the first map
  mdata_input.seekg(levelOffsets[0].count, ios_base::beg);
  readLevelHeader(&mdata_input);


  return 0;
}
