#ifndef READ_MDATA_1
#define READ_MDATA_1

#include "mordorBinaryReader.hpp"

/*
 *  MDATA1.MDR contains guild, race, item, and monster information.
 *  readMDATA1 reads the packed binary representation in this file and
 *  produces structs representing these elements in memory.
 */

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

#endif
