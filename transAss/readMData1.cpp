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
       << "Min Stats: ";

  for(int i = 0; i < 6; i++){
    cout << ret->minStats[i] << " ";
  }
  cout << endl
       << "Max Stats: ";
  for(int i = 0; i < 6; i++){
    cout << ret->maxStats[i] << " ";
  }
  cout << endl << "Resistances: ";
  for(int i = 0; i < 11; i++){
    cout << ret->resistances[i] << " ";
  }
  cout << endl
       << "Alignment: " << ret->alignment << endl
       << "Size: " << ret->size << endl
       << "Bonus Points: " << ret->bonusPoints << endl
       << "Max Age: " << ret->maxAge << endl
       << "expFactor: " << ret->expFactor << endl;
}

race readRace(ifstream *mdata){
  race ret;
  ret.name = readVBString(mdata);
  for(int i = 0; i < 6; i++){
    ret.minStats[i] = readWord(mdata);
  }
  readWord(mdata);
  for(int i = 0; i < 6; i++){
    ret.maxStats[i] = readWord(mdata);
  }
  readWord(mdata);
  for(int i = 0; i < 11; i++){
    ret.resistances[i] = readWord(mdata);
  }
  readWord(mdata);
  ret.alignment = readWord(mdata);
  readWord(mdata);
  ret.size = readWord(mdata);
  ret.bonusPoints = readWord(mdata);
  ret.maxAge = readWord(mdata);
  ret.expFactor = readFloat(mdata);

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
       << "reqStats: ";
  for(int i = 0; i < 6; i++){
    cout << ret->reqStats[i] << " ";
  }
  cout << endl
       << "alignment: " << ret->alignment << endl
       << "ability rates: ";
  for(int i = 0; i < 6; i++){
    cout << ret->abilityRates[i] << " ";
  }
  cout << endl
       << "questPercentage: " << ret->questPercentage << endl
       << "baseMagics: ";
  for(int i = 0; i < 18; i++){
    cout << ret->baseMagics[i] << " ";
  }
  cout << endl
       << "capMagics: ";
  for(int i = 0; i < 18; i++){
    cout << ret->capMagics[i] << " ";
  }
  cout << endl
       << "raceMask: " << ret->raceMask << endl
       << "levelMod: " << ret->levelMod << endl
       << "Attack Increment: " << ret->attackIncrement << endl
       << "Defense Increment: " << ret->defIncrement << endl
       << "AD Cap: " << ret->aDCap << endl
       << "AD Gain: " << ret->aDGain << endl
       << "u3: " << ret->u3 << endl
       << "u7: " << ret->u7 << endl
       << "u8: " << ret->u8 << endl
       << "u16: " << ret->u16 << endl
       << "u17: " << ret->u17 << endl;
}

guild readGuild(ifstream *mdata){
  guild ret;

  ret.name = readVBString(mdata);
  ret.averageHits = readWord(mdata);
  ret.maxLevel = readWord(mdata);
  ret.MH = readWord(mdata);
  ret.expFactor = readFloat(mdata);
  ret.u3 = readWord(mdata);
  for(int i = 0; i < 6; i++){
    ret.reqStats[i] = readWord(mdata);
  }
  readWord(mdata); // dead data?
  ret.alignment = readWord(mdata);
  readWord(mdata); // dead data?
  for(int i = 0; i < 6; i++){
    ret.abilityRates[i] = readFloat(mdata);
  }
  ret.u7 = readWord(mdata);
  ret.u8 = readFloat(mdata);
  readFloat(mdata); //dead data?
  ret.questPercentage = readWord(mdata);
  for(int i = 0; i < 18; i++){
    ret.baseMagics[i] = readFloat(mdata);
  }
  readFloat(mdata); // dead data?
  for(int i = 0; i < 18; i++){
    ret.capMagics[i] = readFloat(mdata);
  }
  ret.raceMask = readDWord(mdata);
  ret.goldRatio = readWord(mdata);
  ret.levelMod = readFloat(mdata);
  ret.attackIncrement = readFloat(mdata);
  ret.defIncrement = readFloat(mdata);
  ret.aDCap = readWord(mdata);
  ret.aDGain = readWord(mdata);
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

  if (! possiblyValidFile(datAbsolutePath, MDATA1)){
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
