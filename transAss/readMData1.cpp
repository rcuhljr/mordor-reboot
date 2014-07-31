
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
  WORD numItemSubptypes;
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

  return 0;
}
