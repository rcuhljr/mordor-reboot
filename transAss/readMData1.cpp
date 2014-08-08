
#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "mordorBinaryReader.hpp"
#include "readMData1.hpp"
#include "assert.h"

using namespace std;

const int RECORD_LENGTH = 260;

struct header{
  char* version;
  WORD numRaces;
  WORD numGuilds;
  WORD numItemSubtypes;
  WORD numItemTypes;
  WORD numMonsterSubtypes;
  WORD numMonsterTypes;
};

void printFileHeader(header *ret){
  cout << "Version:              " << ret->version << endl
       << "Num Races:            " << ret->numRaces << endl
       << "Num Guilds:           " << ret->numGuilds << endl
       << "Num Item Subtypes:    " << ret->numItemSubtypes << endl
       << "Num Item Types:       " << ret->numItemTypes << endl
       << "Num Monster Subtypes: " << ret->numMonsterSubtypes << endl
       << "Num Monster Types:    " << ret->numMonsterTypes << endl;
}

header readFileHeader(ifstream *mdata){
  header ret;

  ret.version = readVBString(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numRaces = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numGuilds = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numItemSubtypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numItemTypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numMonsterSubtypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numMonsterTypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  printFileHeader(&ret);
  return ret;
}

void printRace(race *ret){
  cout << ret->name << endl
       << "Min Stats: " << ret->minStats << endl
       << "Max Stats: " << ret->maxStats << endl
       << "Resistances: " << ret->resistances << endl
       << "Alignment: " << ret->alignment << endl
       << "Size: " << ret->size << endl
       << "Bonus Points: " << ret->bonusPoints << endl
       << "Max Age: " << ret->maxAge << endl
       << "expFactor: " << ret->expFactor << endl;
}

race readRace(ifstream *mdata){
  race ret;
  ret.name = readVBString(mdata);
  ret.minStats = readWord(mdata);
  ret.maxStats = readWord(mdata);
  ret.resistances = readWord(mdata);
  ret.alignment = readDWord(mdata);
  ret.size = readWord(mdata);
  ret.bonusPoints = readWord(mdata);
  ret.maxAge = readWord(mdata);
  ret.expFactor = readDWord(mdata);

  printRace(&ret);
  seekTo(mdata, RECORD_LENGTH);
  return ret;
}

void printGuild(guild *ret){
  cout << ret->name << endl
       << "Avg. Hits: " << ret->averageHits << endl
       << "Max Level: " << ret->maxLevel << endl
       << "MH: " << ret->MH << endl
       << "EXP Factor: " << ret->expFactor << endl
       << "reqStats: " << ret->reqStats << endl
       << "alignment: " << ret->alignment << endl
       << "ability rates: " << ret->abilityRates << endl
       << "questPercentage: " << ret->questPercentage << endl
       << "spellStuff: " << ret->spellStuff << endl
       << "raceMask: " << ret->raceMask << endl
       << "levelMod: " << ret->levelMod << endl
       << "u3: " << ret->u3 << endl
       << "u7: " << ret->u7 << endl
       << "u8: " << ret->u8 << endl
       << "u12: " << ret->u12 << endl
       << "u13: " << ret->u13 << endl
       << "u14: " << ret->u14 << endl
       << "u15: " << ret->u15 << endl
       << "u16: " << ret->u16 << endl
       << "u17: " << ret->u17 << endl;
}

guild readGuild(ifstream *mdata){
  guild ret;

  ret.name = readVBString(mdata);
  ret.averageHits = readWord(mdata);
  ret.maxLevel = readWord(mdata);
  ret.MH = readWord(mdata);
  ret.expFactor = readDWord(mdata);
  ret.u3 = readWord(mdata);
  ret.reqStats = readWord(mdata);
  ret.alignment = readDWord(mdata);
  ret.abilityRates = readDWord(mdata);
  ret.u7 = readWord(mdata);
  ret.u8 = readDWord(mdata);
  ret.questPercentage = readWord(mdata);
  ret.spellStuff = readDWord(mdata);
  ret.raceMask = readWord(mdata);
  ret.u12 = readWord(mdata);
  ret.levelMod = readDWord(mdata);
  ret.u13 = readDWord(mdata);
  ret.u14 = readDWord(mdata);
  ret.u15 = readDWord(mdata);
  ret.u16 = readWord(mdata);
  ret.u17 = readWord(mdata);

  printGuild(&ret);
  seekTo(mdata, RECORD_LENGTH);
  /* Some of the u* values are non 0.

  assert(0 == ret.u3);
  assert(0 == ret.u7);
  assert(0 == ret.u8);
  assert(0 == ret.u12);
  assert(0 == ret.u13);
  assert(0 == ret.u14);
  assert(0 == ret.u15);
  assert(0 == ret.u16);
  assert(0 == ret.u17);
  */
  return ret;
}

void printNamedType(namedTypeID *ret){
  cout << dec << ret->name << "\tID: " << ret->type << endl;
}

namedTypeID readNamedType(ifstream *mdata){
  namedTypeID ret;
  ret.name = readVBString(mdata);
  ret.type = readWord(mdata);
  printNamedType(&ret);
  seekTo(mdata, RECORD_LENGTH);
  return ret;
}


int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << "Expected exactly one argument -- the absolute path to the MDAT1.MDR"
         << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (not possiblyValidFile(datAbsolutePath, MDATA1)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA1.MDR" << endl;
    return 1;
  }

  ifstream mdata(datAbsolutePath, ios::binary | ios::in);

  header h = readFileHeader(&mdata);
  int i = 0;

  cout << endl;
  // races are first
  for(i = 0; i < h.numRaces; i++){
    readRace(&mdata);
    cout << endl;
  }

  // then guilds
  for(i = 0; i < h.numGuilds; i++){
    readGuild(&mdata);
    cout << endl;
  }

  // then item subtypes
  for(i = 0; i < h.numItemSubtypes; i++){
    readNamedType(&mdata);
    cout << endl;
  }

  // then items
  for(i = 0; i < h.numItemTypes; i++){
    readNamedType(&mdata);
    cout << endl;
  }

  // then monster subtypes
  for(i = 0; i < h.numMonsterSubtypes; i++){
    readNamedType(&mdata);
    cout << endl;
  }

  // then monsters
  for(i = 0; i < h.numMonsterTypes; i++){
    readNamedType(&mdata);
    cout << endl;
  }

  return 0;
}
