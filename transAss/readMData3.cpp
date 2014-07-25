
#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "readMData3.hpp"
#include "mordorBinaryReader.hpp"

using namespace std;

const int RECORD_SIZE = 125;
// each field is a 16bit signed integer unless otherwised noted
// so, signed word
// all unused fields have values 0
// first record starts at 0x177 (375 decimal)

struct abilities{
  bool levitate;     //0x01
  bool invisible;    //0x02
  bool protect;      //0x04
  bool seeInvisible; //0x08
  bool criticalHit;  //0x10
  bool backstab;     //0x20
};

struct specialItemMask{
  WORD premanentStatMod;       //0x01 to 0x0A
  WORD spellPointRechargeItem; //0x0B to 0x0E
  WORD ageReducingItem;        //0xC0 to 0xC9
  int guildCrest;             // 0xC0 to 0xC9
};

struct guildMask{
  bool nomad;     //0x001
  bool warrior;   //0x002
  bool paladin;   //0x004
  bool ninja;     //0x008
  bool villain;   //0x010
  bool seeker;    //0x020
  bool thief;     //0x040
  bool scavenger; //0x080
  bool mage;      //0x100
  bool sorcere;   //0x200
  bool wizard;    //0x400
  bool healer;    //0x800

};

struct alignmentMask{
  bool unaligned; //0x01
  bool good;      //0x02
  bool neutral;   //0x04
  bool evel;      //0x08
};

struct resistanceMask{
  bool fire;       //0x001
  bool cold;       //0x002
  bool electrical; //0x004
  bool mind;       //0x008
  bool disease;    //0x010
  bool poison;     //0x020
  bool magic;      //0x040
  bool stone;      //0x080
  bool paralysis;  //0x100
  bool drain;      //0x200
  bool acid;       //0x400
};

struct statSet{
  int strength;     //0x34
  int intellegence; //0x36
  int wisdom;       //0x38
  int constitution; //0x3A
  int charisma;     //0x3C
  int dexterity;    //0x3E
};

struct curseMask{
  bool notCursed;      //0x0
  bool cursedNoEquip;  //0x1
  bool curseAutoEquip; //0x2
};

struct record{
  char* name;             //however much
  int id;                 //0x00
  int attackMod;          //0x02
  int defenceMod;         //0x04
  int itemValue;          //0x06 -- 32bit signed int
  int earliestFindLevel;  //0x0A
  int chanceofFinding;    //0x0C
  abilities abilityMask;  //starting at 0x0E
  int swings;             //0x12
  specialItemMask sim;    //starting at 0x14
  int spellID;            //0x18 -- cross referenced with MDATA2.MDR
  int chargePerCast;      //0x1A
  //unused at 0x1C
  guildMask gm;           //startng at 0x1E
  //unused at 0x20
  int levelScaleFactor;   //0x22
  int damageModifier;     //0x24
  alignmentMask am;       //0x28
  //unused at 0x2A
  int numHands;           //0x2C
  int itemClass;          //starting at 0x2E, running until 0x30
  //unused at 0x32
  statSet statReqs;       //0x34 through 0x3E
  //unused at 0x40
  statSet statMods;       //0x42 through 0x4C
  curseMask cm;           //0x50
  int spellLevel;         //0x52
  bool classRestricted;   //0x54 -- -1 = Yes, 0 = No
};

int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << 
      "Expected exactly one argument -- the absolute path to the MDAT13.MDR" << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (not possiblyValidFile(datAbsolutePath, MDATA3)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA3.MDR" << endl;
    return 1;
  }

  return 0;
}
