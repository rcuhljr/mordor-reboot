
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
  cout << ret->version << "\tNum Monsters: "
       << ret->numMonsters << endl;
}

header readHeader(ifstream *mdata){
  header ret;

  ret.version = readVBString(mdata);
  ret.numMonsters = readWord(mdata);
 
  printHeader(&ret);
  return ret;
}

void printMonster(monster *m){
  cout << m->name << endl
       << m->attackRating << endl
       << m->defenceRating << endl
       << m->id << endl
       << m->hitPoints << endl
       << m->groupSize << endl
       << m->portaitID << endl
       << m->u8 << endl
       << m->appearOnLevel << endl
       << m->fireResistance << endl
       << m->coldResistance << endl
       << m->electricalResistance << endl
       << m->mindResistance << endl
       << m->diseaseResistance << endl
       << m->poisonResistance << endl
       << m->magicResistance << endl
       << m->stoneResistance << endl
       << m->paralysisResistance << endl
       << m->drainResistance << endl
       << m->acidResistance << endl
       << m->u21 << endl
       << m->u22 << endl
       << m->u23 << endl
       << m->u24 << endl
       << m->u25 << endl
       << m->u26 << endl
       << m->u27 << endl
       << m->encounterChance << endl
       << m->nothingChance << endl
       << m->boxChance << endl
       << m->chestChance << endl
       << m->u32 << endl
       << m->u33 << endl
       << m->u34 << endl
       << m->u35 << endl
       << m->u36 << endl
       << m->u37 << endl
       << m->u38 << endl
       << m->strength << endl
       << m->intelligence << endl
       << m->wisdom << endl
       << m->constitution << endl
       << m->dexterity << endl
       << m->u45 << endl
       << m->u46 << endl
       << m->u47 << endl
       << m->u48 << endl
       << m->u49 << endl
       << m->u50 << endl
       << m->u51 << endl
       << m->u52 << endl;
}

monster readMonster(ifstream *mdata){
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
