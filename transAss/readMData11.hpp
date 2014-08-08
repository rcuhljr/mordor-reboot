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
  CURRENCY fieldMask;    // 8 bytes
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
  WORD monsterID;
};

#endif
