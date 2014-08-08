#ifndef READ_MDATA_11
#define READ_MDATA_11
#include "mordorBinaryReader.hpp"

const int MAX_LAIRS_PER_LEVEL = 200;
const int MAX_WIDTH = 30;
const int MAX_HEIGHT = 30;

struct mapHeader{
  WORD numLevels;
  int *levelOffsets;
};

struct levelHeader {
  WORD width;
  WORD height;
  WORD levelNumber;
  WORD numLairs;
  WORD numChutes;
  WORD numTeleports;
};

struct fieldMask{
  bool eastWall;
  bool northWoll;
  bool eastDoor;
  bool northDoor;
  bool eastSecretDoor;
  bool northSecterDoor;
  bool faceNorth;
  bool faceEast;
  bool faceSouth;
  bool faceWest;
  bool extingusher;
  bool pit;
  bool stairsUp;
  bool stairsDown;
  bool teleporter;
  bool water;
  bool quicksand;
  bool rotator;
  bool antimagic;
  bool rock;
  bool fog;
  bool chute;
  bool stud;
};

struct fieldRecord {
  WORD spawnAreaID;
  BYTE fieldMask[8];    // 8 bytes
  struct fieldMask fieldContents;
};

struct areaRecord {
  DWORD spawnTypeMask; // 4 bytes
  WORD lairID;
};

struct spawnMask{
  bool humanoid;
  bool cleanup;
  bool demon;
  bool devil;
  bool elemental;
  bool reptile;
  bool dragon;
  bool animal;
  bool insect;
  bool undead;
  bool water;
  bool giant;
  bool mythical;
  bool lycanthrope;
  bool thief;
  bool mage;
  bool warrior;
  bool indigini;
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
  spawnMask spawnMask;
  WORD monsterID;
};

struct level{
  levelHeader lh;
  fieldRecord *fields;
  teleporterRecord *teleporters;
  chuteRecord *chutes;
  monsterLair *monsterLairs;
};

/*
 * Field records are stored in a linear way instead of in a 2d array.
 * These functions help convert the index into the field array of a level
 * into easier to understand x,y coordinates.
 */
int cellX(int index, levelHeader *lh);
int cellY(int index, levelHeader *lh);

/*
 * Returns the header of the map file from a file stream.
 * Leaves the pointer at the end of the last offset record read.
 */
struct mapHeader readMapHeader(ifstream *mdata);

/*
 *  Reads in a level from a file stream, using a levelHeader to find
 *  the level and validate it's contents.  It expects the mdata stream
 *  to be pointing at the begining of the level.  That is, you need to
 *  seek to the start of the level using the offsets in the mapHeader
 *  structure.
 */
struct level readLevel(ifstream *mdata, levelHeader *lh);

#endif
