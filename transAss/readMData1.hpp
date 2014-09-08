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
  WORD minStats[6];
  WORD maxStats[6];
  WORD resistances[11];
  WORD alignment;
  WORD size;
  WORD bonusPoints;
  WORD maxAge;
  float expFactor;
};

struct guild{
  char* name;
  WORD averageHits;
  WORD maxLevel;
  WORD MH;               // ??
  float expFactor;
  WORD u3;               // ??
  WORD reqStats[6];
  WORD alignment;
  float abilityRates[6];
  WORD u7;               // ??
  float u8;              // ??
  WORD questPercentage;
  float baseMagics[18];
  float capMagics[18];
  WORD raceMask;
  WORD goldRatio;               //??
  float levelMod;         //??
  float attackIncrement;
  float defIncrement;
  WORD aDCap;
  float aDGain;
  WORD u16, u17;         // ??
};

// works for sub item, item, sub monster, monster
struct namedTypeID{
  char* name;
  WORD type;
};

#endif
