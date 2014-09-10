#ifndef READ_MDATA_1
#define READ_MDATA_1

#include "mordorBinaryReader.hpp"

/*
 *  MDATA1.MDR contains guild, race, item, and monster information.
 *  readMDATA1 reads the packed binary representation in this file and
 *  produces structs representing these elements in memory.
 */

const unsigned short GOOD = 0x0001;
const unsigned short NEUTRAL = 0x0002;
const unsigned short EVIL = 0x0004;

const unsigned short HUMAN = 0x0001;
const unsigned short ELF = 0x0002;
const unsigned short GIANT = 0x0004;
const unsigned short GNOME = 0x0008;
const unsigned short DWARF = 0x0010;
const unsigned short OGRE = 0x0020;
const unsigned short MORLOCH = 0x0040;
const unsigned short OSIRI = 0x0080;
const unsigned short TROLL = 0x0100;

struct race{
  char* name;
  WORD minStats[6];
  WORD maxStats[6];
  WORD resistances[11];
  bool alignment[3];
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
  bool alignment[3];
  float abilityRates[6];
  WORD u7;               // ??
  float u8;              // ??
  WORD questPercentage;
  float baseMagics[18];
  float capMagics[18];
  bool races[9];
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
