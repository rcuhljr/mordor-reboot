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

const int RECORD_SIZE = 20;

int numLevels = -1;

const unsigned int humanoid = 1;
const unsigned int cleanup = 2;
const unsigned int demon = 4;
const unsigned int devil = 8;
const unsigned int elemental = 16;
const unsigned int reptile = 32;
const unsigned int dragon = 64;
const unsigned int animal = 128;
const unsigned int insect = 256;
const unsigned int undead = 512;
const unsigned int waterMonster = 1024;
const unsigned int giant = 2048;
const unsigned int mythical = 4096;
const unsigned int lycanthrope = 8192;
const unsigned int thief = 16384;
const unsigned int mage = 32768;
const unsigned int warrior = 65536;
const unsigned int indigini = 131072;

struct mapHeader{
  WORD numLevels;
  int *levelOffsets;
};

struct countHeader { //area, teleport, chute header
  int count;
};

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
  struct fieldMask fm;

  fm.eastWall = ret.fieldMask[0] & 1;
  fm.northWoll = ret.fieldMask[0] & 2;
  fm.eastDoor = ret.fieldMask[0]  & 4;
  fm.northDoor = ret.fieldMask[0] & 8;
  fm.eastSecretDoor = ret.fieldMask[1] & 1;
  fm.northSecterDoor = ret.fieldMask[1] & 2;
  fm.faceNorth = ret.fieldMask[1] & 4;
  fm.faceEast = ret.fieldMask[1] & 8;
  fm.faceSouth = ret.fieldMask[2] & 1;
  fm.faceWest = ret.fieldMask[2] & 2;
  fm.extingusher = ret.fieldMask[2] & 4;
  fm.pit = ret.fieldMask[2] & 8;
  fm.stairsUp = ret.fieldMask[3] & 1;
  fm.stairsDown = ret.fieldMask[3] & 2;
  fm.teleporter = ret.fieldMask[3] & 4;
  fm.water = ret.fieldMask[3] & 8;
  fm.quicksand = ret.fieldMask[4] & 1;
  fm.rotator = ret.fieldMask[4] & 2;
  fm.antimagic = ret.fieldMask[4] & 4;
  fm.rock = ret.fieldMask[4] & 8;
  fm.fog = ret.fieldMask[5] & 1;
  fm.chute = ret.fieldMask[5] & 2;
  fm.stud = ret.fieldMask[5] & 4;
  
  ret.fieldContents = fm;
#ifdef LOUD
  printFieldRecord(&ret);
#endif

  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printMonsterLair(monsterLair *ret){
  cout << "MonsterType: " << ret->monsterType << endl
       << "MonsterID:   " << ret->monsterID << endl;
}

monsterLair readMonsterLair(ifstream *mdata){
  monsterLair ret;
  ret.monsterType = readDWord(mdata);
  ret.monsterID = readWord(mdata);

  spawnMask sm; 
  sm.humanoid = ret.monsterType & humanoid;
  sm.cleanup = ret.monsterType & cleanup;
  sm.demon = ret.monsterType & demon;
  sm.devil = ret.monsterType & devil;
  sm.elemental = ret.monsterType & elemental;
  sm.reptile = ret.monsterType & reptile;
  sm.dragon = ret.monsterType & dragon;
  sm.animal = ret.monsterType & animal;
  sm.insect = ret.monsterType & insect;
  sm.undead = ret.monsterType & undead;
  sm.water = ret.monsterType & waterMonster;
  sm.giant = ret.monsterType & giant;
  sm.mythical = ret.monsterType & mythical;
  sm.lycanthrope = ret.monsterType & lycanthrope;
  sm.thief = ret.monsterType & thief;
  sm.mage = ret.monsterType & mage;
  sm.warrior = ret.monsterType & warrior;
  sm.indigini = ret.monsterType & indigini;

  ret.spawnMask = sm;

#ifdef LOUD
  printMonsterLair(&ret);
#endif

  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printCountHeader(countHeader *ret){
  cout << "Count: " << ret->count << endl;
}

countHeader readCountHeader(ifstream *mdata){
  countHeader ret;
  ret.count = readWord(mdata);
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

#ifdef LOUD
  printAreaRecord(&ret);
#endif

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

  //build the teleporter
  ret.srcX = readWord(mdata);
  ret.srcY = readWord(mdata);
  ret.destX = readWord(mdata);
  ret.destY = readWord(mdata);
  ret.destZ = readWord(mdata);

  // make sure the teleporter is sane
  assert(MAX_WIDTH >= ret.srcX >= 0);
  assert(MAX_HEIGHT >= ret.srcY >= 0);
  assert(MAX_WIDTH >= ret.destX >= 0);
  assert(MAX_HEIGHT >= ret.destY >= 0);
  assert(numLevels >= ret.destZ >= 0);  

  //display and return
#ifdef LOUD
  printTeleporterRecord(&ret);
#endif

  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printChuteRecord(chuteRecord *ret){
  cout << "X: " << ret->x << "\tY: " << ret->y << "\tZ: " << ret->dropDepth << endl;
}

chuteRecord readChuteRecord(ifstream *mdata){
  chuteRecord ret;
  // read in the chute
  ret.x = readWord(mdata);
  ret.y = readWord(mdata);
  ret.dropDepth = readWord(mdata);
  
  /* 
   * sanity check what you can while you read it you can't make sure
   * that the depth doesn't run you off of the board here though, not
   * completely, because you don't have the depth of the level that
   * you're reading the chute on.
   */
  assert(MAX_WIDTH >= ret.x >= 0);
  assert(MAX_HEIGHT >= ret.y >= 0);
  assert(numLevels >= ret.dropDepth > 0);

  //display and return
#ifdef LOUD
  printChuteRecord(&ret);
#endif
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

void printLevelHeader(levelHeader *lh){
  cout << dec 
       << "Width:     " << lh->width << endl
       << "Height:    " << lh->height << endl
       << "Level:     " << lh->levelNumber << endl
       << "Areas:     " << lh->numLairs << endl
       << "Chutes:    " << lh->numChutes << endl
       << "Teleports: " << lh->numTeleports << endl;
}

levelHeader readLevelHeader(ifstream *mdata_input){
  levelHeader thisLevel;

  //read the level in
  thisLevel.width = readWord(mdata_input);
  thisLevel.height = readWord(mdata_input);
  thisLevel.levelNumber = readWord(mdata_input);
  thisLevel.numLairs = readWord(mdata_input);
  thisLevel.numChutes = readWord(mdata_input);
  thisLevel.numTeleports = readWord(mdata_input);

  // quick validation checks
  assert(thisLevel.width == MAX_WIDTH);
  assert(thisLevel.height == MAX_HEIGHT);
  assert(numLevels >= thisLevel.levelNumber >= 0);

  // display and return
  printLevelHeader(&thisLevel);

  seekTo(mdata_input, RECORD_SIZE);
  return thisLevel;
}

void readLevel(ifstream *mdata_input, levelHeader *lh){

  int num_fields = lh->width * lh->height;
  fieldRecord fieldRecords[num_fields];
  int i;

  // read the map cells
#ifdef LOUD
  cout << "Number of Map Cells: " << num_fields << endl;
#endif
  for(i = 0; i < num_fields; i++){
    fieldRecords[i] = readFieldRecord(mdata_input);
  }

  // read monster lair records
  countHeader monsterLairHeader = readCountHeader(mdata_input);
  monsterLair monsterLairs[monsterLairHeader.count];
#ifdef LOUD
  cout << "Num Lairs: " << monsterLairHeader.count << endl;
#endif
  assert(monsterLairHeader.count == lh->numLairs);
  assert(monsterLairHeader.count <= MAX_LAIRS_PER_LEVEL);

  for(i = 0; i < monsterLairHeader.count; i++){
    monsterLairs[i] = readMonsterLair(mdata_input);
  }

  // now that I've read the meningful lairs, clear out the rest of the set.
  // the setis bounded from  above by 200.
  for(; i < MAX_LAIRS_PER_LEVEL; i++){
    seekTo(mdata_input, RECORD_SIZE);
  }

  // I have to strip off an additional record here, and I don't know why.
  seekTo(mdata_input, RECORD_SIZE);

  //teleport header
  countHeader teleportHeader = readCountHeader(mdata_input);
#ifdef LOUD
  cout << "Num Teleporters: " << teleportHeader.count << endl;
#endif
  assert(teleportHeader.count == lh->numTeleports);
  teleporterRecord teleportRecords[teleportHeader.count];
  for(i = 0; i < teleportHeader.count; i++){
    teleportRecords[i] = readTeleporterRecord(mdata_input);
  }


  //chute header
  countHeader chuteHeader = readCountHeader(mdata_input);
#ifdef LOUD
  cout << "Num Chutes: " << chuteHeader.count << endl;
#endif
  assert(chuteHeader.count == lh->numChutes);
  chuteRecord chuteRecords[chuteHeader.count];
  int maxDrop = numLevels - lh->levelNumber;
  for(i = 0; i < chuteHeader.count; i++){
    chuteRecords[i] = readChuteRecord(mdata_input);
    assert(maxDrop >= chuteRecords[i].dropDepth);
  }

  //and here is wher we would construct the level object
}

mapHeader readMapHeader(ifstream *mdata){
  mapHeader ret;
  ret.numLevels = readWord(mdata);
  seekTo(mdata,RECORD_SIZE);
  ret.levelOffsets = new int[ret.numLevels];
  for(int i = 0; i < ret.numLevels; i++){
    WORD read = readWord(mdata);
    ret.levelOffsets[i] = RECORD_SIZE * (read - 1); // -1 taken from wabbits editor
    seekTo(mdata, RECORD_SIZE);
  }
  // set global num levels by side effect.
  numLevels = ret.numLevels;
  return ret;
}

// testing main point -- this won't be compiled on it's own
int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr 
      << "Expected exactly one argument -- the absolute path to the MDAT11.MDR" 
      << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (not possiblyValidFile(datAbsolutePath, MDATA11)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA11.MDR" << endl;
    return 1;
  }

  ifstream mdata_input(datAbsolutePath, ios::binary | ios::in);
  mapHeader mh = readMapHeader(&mdata_input);

  cout << "Num levels: " << mh.numLevels << endl;

  // try to read the first map
  for(int i = 0; i < mh.numLevels; i++){
    cout << endl;
    mdata_input.seekg(mh.levelOffsets[i], ios_base::beg);
    levelHeader lh = readLevelHeader(&mdata_input);
    readLevel(&mdata_input, &lh);
  }


  return 0;
}
