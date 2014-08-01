#ifndef READ_MDATA_11
#define READ_MDATA_11
#include "mordorBinaryReader.hpp"

struct levelHeader {
  WORD width;
  WORD height;
  WORD levelNumber;
  WORD numAreas;
  WORD numChutes;
  WORD numTeleports;
};

struct fieldRecord {
  WORD spawnAreaID;
  BYTE fieldMask[8];    // 8 bytes
};

struct countHeader { //area, teleport, chute header, level offset
  WORD count;
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

#endif
