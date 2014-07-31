
#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "mordorBinaryReader.hpp"
#include "readMData1.hpp"

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

struct race{
  char* name;
  WORD minStats;
  WORD maxStats;
  WORD resistances;
  DWORD alignment;
  WORD size;
  WORD bonusPoints;
  WORD maxAge;
  DWORD expFactor;
};

struct guild{
  char* name;
  WORD averageHits;
  WORD maxLevel;
  WORD MH;               // ??
  DWORD expFactor;
  WORD u3;               // ??
  WORD reqStats;
  DWORD alignment;
  DWORD abilityRates;
  WORD u7;               // ??
  DWORD u8;              // ??
  WORD questPercentage;
  DWORD spellStuff;
  DWORD raceMask;
  WORD u12;               //??
  DWORD levelMod;         //??
  DWORD u13, u14, u15;   // ??
  WORD u16, u17;         // ??
};

// works for sub item, item, sub monster, monster
struct namedTypeID{
  char* name;
  WORD type;
};

void printFileHeader(header *ret){
  cout << "Version:              " << ret->version << endl;
  cout << "Num Races:            " << ret->numRaces << endl;
  cout << "Num Guilds:           " << ret->numGuilds << endl;
  cout << "Num Item Subtypes:    " << ret->numItemSubtypes << endl;
  cout << "Num Item Types:       " << ret->numItemTypes << endl;
  cout << "Num Monster Subtypes: " << ret->numMonsterSubtypes << endl;
  cout << "Num Monster Types:    " << ret->numMonsterTypes << endl;
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
       << ret->averageHits << endl
       << ret->maxLevel << endl
       << ret->MH << endl
       << ret->expFactor << endl
       << ret->u3 << endl
       << ret->reqStats << endl
       << ret->alignment << endl
       << ret->abilityRates << endl
       << ret->u7 << endl
       << ret->u8 << endl
       << ret->questPercentage << endl
       << ret->spellStuff << endl
       << ret->raceMask << endl
       << ret->u12 << endl
       << ret->levelMod << endl
       << ret->u13 << endl
       << ret->u14 << endl
       << ret->u15 << endl
       << ret->u16 << endl
       << ret->u17 << endl;
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
    cerr << "Expected exactly one argument -- the absolute path to the MDAT1.MDR" << endl;
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
