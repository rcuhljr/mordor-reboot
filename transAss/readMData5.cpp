
#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "mordorBinaryReader.hpp"
#include "readMData5.hpp"
#include "assert.h"

using namespace std;

struct header{
  char* version;
  WORD numMonsters;
};

struct monster{
  char* name;
  WORD attackRating;
  WORD defenceRating;
  WORD id;
  WORD hitPoints;
  WORD groupSize;
  WORD portaitID;
  WORD u8;
  WORD appearOnLevel;
  WORD fireResistance;
  WORD coldResistance;
  WORD electricalResistance;
  WORD mindResistance;
  WORD diseaseResistance;
  WORD poisonResistance;
  WORD magicResistance;
  WORD stoneResistance;
  WORD paralysisResistance;
  WORD drainResistance;
  WORD acidResistance;
  WORD u21, u22, u23, u24, u25, u26, u27;
  WORD encounterChance;
  WORD nothingChance;
  WORD boxChance;
  WORD chestChance;
  WORD u32, u33, u34, u35, u36, u37, u38;
  WORD strength;
  WORD intelligence;
  WORD wisdom;
  WORD constitution;
  WORD dexterity;
  WORD u45, u46, u47, u48, u49, u50, u51, u52;
};

void printHeader(const header *ret){
}

header readHeader(const ifstream *mdata){
  header ret;
 
  printHeader(&ret);
  return ret;
}

void printMonster(monster *m){
}

monster readMonster(const ifstream *mdata){
  monster ret;
  
  printMonster(&ret);
  return ret;
}

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
