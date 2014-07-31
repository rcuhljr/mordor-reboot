
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
       << "Attack Rating: " << m->attackRating << endl
       << "defenceRating" << m->defenceRating << endl
       << "ID" << m->id << endl
       << "HP" << m->hitPoints << endl
       << "groupSize" << m->groupSize << endl
       << "portraitID" << m->portaitID << endl
       << "u8" << m->u8 << endl
       << "appearOnLevel" << m->appearOnLevel << endl
       << "fireResistance" << m->fireResistance << endl
       << "coldResistance" << m->coldResistance << endl
       << "electricalResistance" << m->electricalResistance << endl
       << "mindResistance" << m->mindResistance << endl
       << "diseaseResistance" << m->diseaseResistance << endl
       << "poisonResistance" << m->poisonResistance << endl
       << "magicResistance" << m->magicResistance << endl
       << "stoneResistance" << m->stoneResistance << endl
       << "paralyisResistance" << m->paralysisResistance << endl
       << "drainResistance" << m->drainResistance << endl
       << "acidResistance" << m->acidResistance << endl
       << "u21" << m->u21 << endl
       << "u22" << m->u22 << endl
       << "u23" << m->u23 << endl
       << "u24" << m->u24 << endl
       << "u25" << m->u25 << endl
       << "u26" << m->u26 << endl
       << "u27" << m->u27 << endl
       << "encounterChance" << m->encounterChance << endl
       << "nothingChance" << m->nothingChance << endl
       << "boxChance" << m->boxChance << endl
       << "chestChance" << m->chestChance << endl
       << "u32" << m->u32 << endl
       << "u33" << m->u33 << endl
       << "u34" << m->u34 << endl
       << "u35" << m->u35 << endl
       << "u36" << m->u36 << endl
       << "u37" << m->u37 << endl
       << "u38" << m->u38 << endl
       << "strength" << m->strength << endl
       << "intelligence" << m->intelligence << endl
       << "wisdom" << m->wisdom << endl
       << "constitution" << m->constitution << endl
       << "dexterity" << m->dexterity << endl
       << "u45" << m->u45 << endl
       << "u46" << m->u46 << endl
       << "u47" << m->u47 << endl
       << "u48" << m->u48 << endl
       << "u49" << m->u49 << endl
       << "u50" << m->u50 << endl
       << "u51" << m->u51 << endl
       << "u52" << m->u52 << endl;
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
