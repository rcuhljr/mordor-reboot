#ifndef READ_MDATA_11
#define READ_MDATA_11
#include "mordorBinaryReader.hpp"

const int MAX_LAIRS_PER_LEVEL = 200;
const int MAX_WIDTH = 30;
const int MAX_HEIGHT = 30;

struct levelHeader {
  WORD width;
  WORD height;
  WORD levelNumber;
  WORD numLairs;
  WORD numChutes;
  WORD numTeleports;
};

struct fieldRecord {
  WORD spawnAreaID;
  BYTE fieldMask[8];    // 8 bytes
};

struct countHeader { //area, teleport, chute header, level offset
  int count;
};

struct areaRecord {
  DWORD spawnTypeMask; // 4 bytes
  WORD lairID;
};

struct teleporterRecord{
  WORD srcX;
  WORD srcY;
  WORD destX;
  WORD destY;
  WORD destZ;
};

struct chuteRecord {
  WORD x;
  WORD y;
  WORD dropDepth;
};

struct monsterLair{
  DWORD monsterType;
  WORD monsterID;
};

#endif
