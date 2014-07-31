
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
}

race readRace(ifstream *mdata){
  race ret;

  printRace(&ret);
  return ret;
}

void printGuild(guild *ret){
}

guild readGuild(ifstream *mdata){
  guild ret;

  printGuild(&ret);
  return ret;
}

void printNamedType(namedTypeID *ret){
}

namedTypeID readNamedType(ifstream *mdata){
  namedTypeID ret;
  
  printNamedType(&ret);
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

  // races are first
  for(i = 0; i < h.numRaces; i++){
  }

  // then guilds
  for(i = 0; i < h.numGuilds; i++){
  }

  // then item subtypes
  for(i = 0; i < h.numItemSubtypes; i++){
  }

  // then items
  for(i = 0; i < h.numItemTypes; i++){
  }

  // then monster subtypes
  for(i = 0; i < h.numMonsterSubtypes; i++){
  }

  // then monsters
  for(i = 0; i < h.numMonsterTypes; i++){
  }

  return 0;
}
