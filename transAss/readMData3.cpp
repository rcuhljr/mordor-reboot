
#include <iostream>
#include <fstream>
#include <assert.h>

#include "mdataTools.hpp"
#include "mordorBinaryReader.hpp"
#include "readMData3.hpp"


using namespace std;

const int RECORD_SIZE = 125;
const int NUM_RECORDS = 365;

struct specialItemMask{
  WORD permanentStatMod;       //0x01 to 0x0A
  WORD spellPointRechargeItem; //0x0B to 0x0E
  WORD ageReducingItem;        //0xC0 to 0xC9
  int guildCrest;             // 0xC0 to 0xC9
};

struct abilities{
  bool levitate;     //0x01
  bool invisible;    //0x02
  bool protect;      //0x04
  bool seeInvisible; //0x08
  bool criticalHit;  //0x10
  bool backstab;     //0x20
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
  bool sorceror;   //0x200
  bool wizard;    //0x400
  bool healer;    //0x800

};

struct alignmentMask{
  bool unaligned; //0x01
  bool good;      //0x02
  bool neutral;   //0x04
  bool evil;      //0x08
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
  int intelligence; //0x36
  int wisdom;       //0x38
  int constitution; //0x3A
  int charisma;     //0x3C
  int dexterity;    //0x3E
};

struct curseMask{
  bool notCursed;      //0x0
  bool cursedNoEquip;  //0x1
  bool cursedAutoEquip; //0x2
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
  int spellID2;            //0x18 -- cross referenced with MDATA2.MDR
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


void printAbilityMask(const abilities *ret){
  cout << "abilities:\t";
  if (ret->levitate){
    cout << "Levitates ";
  }
  if (ret ->invisible){
    cout << "Invisible ";
  }
  if (ret->protect){
    cout << "Protects ";
  }
  if (ret->seeInvisible){
    cout << "See Invisible ";
  }
  if (ret->criticalHit){
    cout << "Critical Hit ";
  }
  if (ret->backstab){
    cout << "Backstab ";
  }
  cout << endl;
}

abilities readAbilityMask(ifstream *mdata){
  //0x0E to 0x11 -- 3 bytes
  BYTE b1 = readByte(mdata); //SPIL
  BYTE b2 = readByte(mdata); //XXBC
  abilities ret;

  ret.levitate     = b1 & 0x01;
  ret.invisible    = b1 & 0x02;
  ret.protect      = b1 & 0x04;
  ret.seeInvisible = b1 & 0x08;
  ret.criticalHit  = b2 & 0x10;
  ret.backstab     = b2 & 0x20;
  printAbilityMask(&ret);
  return ret;
}

void printGuildMask(const guildMask *ret){
  cout << "Useable by: ";

  if(ret->nomad){
    cout << "Nomad ";
  }
  if(ret->warrior){
    cout << "Warrior ";
  }
  if(ret->paladin){
    cout << "Paladin ";
  }
  if(ret->ninja){
    cout << "Ninja ";
  }
  if(ret->villain){
    cout << "Villain ";
  }
  if(ret->seeker){
    cout << "Seeker ";
  }
  if(ret->thief){
    cout << "Thief ";
  }
  if(ret->scavenger){
    cout << "Scavenger ";
  }
  if(ret->mage){
    cout << "Mage ";
  }
  if(ret->sorceror){
    cout << "Sorceror ";
  }
  if(ret->wizard){
    cout << "Wizard ";
  }
  if(ret->healer){
    cout << "Healer ";
  }
  cout << endl;
}

guildMask readGuildMask(ifstream *mdata){
  WORD data = readWord(mdata);
  guildMask ret;

  // I don't know if any of these are simultaneously set, so fill out the mask
  ret.nomad = data & 0x001;
  ret.warrior = data & 0x002;
  ret.paladin = data & 0x004;
  ret.ninja = data & 0x008;
  
  ret.villain = data & 0x010;
  ret.seeker = data & 0x020;
  ret.thief = data & 0x040;
  ret.scavenger = data & 0x080;

  ret.mage = data & 0x100;
  ret.sorceror = data & 0x200;
  ret.wizard = data & 0x400;
  ret.healer = data & 0x800;

  printGuildMask(&ret);
  return ret;
}

 guildMask readGuildMaskOld(ifstream *mdata){
  BYTE b1 = readByte(mdata);
  BYTE b2 = readByte(mdata);
  BYTE b3 = readByte(mdata);

  guildMask ret;

  ret.nomad = b1 & 0x1;
  ret.warrior = b1 & 0x2;
  ret.paladin = b1 & 0x4;
  ret.ninja = b1 & 0x8;

  ret.villain = b2 & 0x1;
  ret.seeker = b2 & 0x2;
  ret.thief = b2 & 0x4;
  ret.scavenger = b2 & 0x8;

  ret.mage = b3 & 0x1;
  ret.sorceror = b3 & 0x2;
  ret.wizard = b3 & 0x4;
  ret.healer = b3 & 0x8;
 
  printGuildMask(&ret);
   return ret;
 }

void printAlignmentMask(const alignmentMask *ret){
  cout << "Useable by: ";
  if(ret->unaligned){
    cout << "Unaligned ";
  }
  if(ret->good){
    cout << "Good ";
  }
  if(ret->neutral){
    cout << "Neutral ";
  }
  if(ret->evil){
    cout << "Evil ";
  }
  cout << endl;
}

alignmentMask readAlignmentMask(ifstream *mdata){
  BYTE b1 = readByte(mdata);
  alignmentMask ret;
  
  ret.unaligned = b1 & 0x01;
  ret.good = b1 & 0x02;
  ret.neutral = b1 & 0x04;
  ret.evil = b1 & 0x08;
  
  printAlignmentMask(&ret);
  return ret;
}

void printResistanceMask(const resistanceMask *ret){
  cout << "Resists: ";

  if(ret->fire){
    cout << "Fire ";
  }
  if(ret->cold){
    cout << "Cold ";
  }
  if(ret->electrical){
    cout << "Electrical ";
  }
  if(ret->mind){
    cout << "Mind ";
  }
  if(ret->disease){
    cout << "Disease ";
  }
  if(ret->poison){
    cout << "Poison ";
  }
  if(ret->magic){
    cout << "Magic ";
  }
  if(ret->stone){
    cout << "Stone ";
  }
  if(ret->paralysis){
    cout << "Paralysis ";
  }
  if(ret->drain){
    cout << "Drain ";
  }
  if(ret->acid){
    cout << "Acid ";
  }
 cout << endl;
}

resistanceMask readResistances(ifstream *mdata){
  BYTE b1 = readWord(mdata);
  BYTE b2 = readWord(mdata);
  BYTE b3 = readWord(mdata);
  resistanceMask ret;

  ret.fire = b1 & 0x01;
  ret.cold = b1 & 0x02;
  ret.electrical = b1 & 0x04;
  ret.mind = b1 & 0x08;
  
  ret.disease = b2 & 0x01;
  ret.poison = b2 & 0x02;
  ret.magic = b2 & 0x04;
  ret.stone = b2 & 0x08;

  ret.paralysis = b3 & 0x01;
  ret.drain = b3 & 0x02;
  ret.acid = b3 & 0x04;

  printResistanceMask(&ret);
  return ret;
}

void printStatSet(const statSet *ret){
  cout << "STR: " << ret->strength << endl;
  cout << "INT: " << ret->intelligence << endl;
  cout << "WIS: " << ret->wisdom << endl;
  cout << "CON: " << ret->constitution << endl;
  cout << "CHA: " << ret->charisma << endl;
  cout << "DEX: " << ret->dexterity << endl;
}

statSet readStatSet(ifstream *mdata){
  statSet ret;
  // these may need to be signed words instead of unsigned words
  ret.strength = readWord(mdata);
  ret.intelligence = readWord(mdata);
  ret.wisdom = readWord(mdata);
  ret.constitution = readWord(mdata);
  ret.charisma = readWord(mdata);
  ret.dexterity = readWord(mdata);

  printStatSet(&ret);
  return ret;
}

void printCurseMask(const curseMask *ret){
  if(ret->notCursed){
    cout << "Not Cursed" << endl;
  }
  if(ret->cursedNoEquip){
    cout << "Cursed" << endl;
  }
  if(ret->cursedAutoEquip){
    cout << "Cursed, Automatically Equips" << endl;
  }
}

curseMask readCurseMask(ifstream *mdata){
  BYTE b1 = readByte(mdata);
  BYTE b2 = readByte(mdata);
  curseMask ret;

  ret.notCursed = b1 == 0;
  ret.cursedNoEquip = b1 == 1;
  ret.cursedAutoEquip = b1 == 2;

  printCurseMask(&ret);
  return ret;
}

void printSpecialItemMask(const specialItemMask *ret){
}

specialItemMask readSpecialItemMask(ifstream *mdata){
  //permanentStatMod 0x01 to 0x0A -- 10 values, discad the first byte?
  //spellPointRechargeItem 0x0B to 0x0C -- just a word
  //ageReducingItem 0x0D to 0x0E        -- just a word
  //guild crest 0xC0 to 0xC9            -- 10 values -- guild mask?
  specialItemMask ret; 
  WORD data = readWord(mdata);
  
  cout << hex << "Special Item mask " << data << dec << endl;
  //fixme stub

  printSpecialItemMask(&ret);
  return ret;
}

int readItemClass(ifstream *mdata){
  /*
0x00 = Hands
0x01 = Dagger
0x02 = Cross
0x03 = Sword
0x04 = Staff
0x05 = Mace
0x06 = Axe
0x07 = Hammer
0x08 = Leather Armour
0x09 = Chain Armour
0x0A = Plate Armour
0x0B = Shield
0x0C = Cap
0x0D = Helmet
0x0E = Gloves
0x0F = Gauntlets
0x10 = Cloak
0x11 = Bracers
0x12 = Sash
0x13 = Girdle
0x14 = Boots
0x15 = Ring
0x16 = Amulet
0x17 = Potion
0x18 = Scroll
0x19 = Tome
0x1A = Dust
0x1B = Crystal
0x1C = Rod
0x1D = Stone
0x1E = Sphere
0x1F = Cube
0x20 = Artifact
0x21 = Misc Item
0x22 = Guild Crest
0x30: Resistances granted (bitmask)
0x001 = Fire res
0x002 = Cold res
0x004 = Electrical res
0x008 = Mind res
0x010 = Disease res
0x020 = Poison res
0x040 = Magic res
0x080 = Stone res
0x100 = Paralysis res
0x200 = Drain res
0x400 = Acid res
*/

    WORD classID = readWord(mdata);
    return -1;
}


void printItem(ifstream *mdata){
  assert(false);
}

record readItem(ifstream *mdata){
  record ret;
  
  ret.name = readVBString(mdata);
  cout << "Reading: " << ret.name << endl;
  ret.id = readWord(mdata);                   //0x00
  ret.attackMod = readWord(mdata);
  ret.defenceMod = readWord(mdata);
  ret.itemValue = readInt(mdata);
  

  cout << "Cost: " << ret.itemValue << endl;
  ret.earliestFindLevel = readWord(mdata);
  ret.chanceofFinding = readWord(mdata);
  ret.abilityMask = readAbilityMask(mdata);
  
  assert(checkAlignment(mdata));
  ret.swings = readWord(mdata);
  ret.sim = readSpecialItemMask(mdata);
  ret.spellID = readWord(mdata);
  ret.spellID2 = readWord(mdata);
  ret.chargePerCast= readWord(mdata);
  assert(checkAlignment(mdata));              //0x1C
  
  ret.gm = readGuildMask(mdata);
  
  assert(checkAlignment(mdata));              //0x20
  ret.levelScaleFactor = readWord(mdata);
  ret.damageModifier = readInt(mdata);
  ret.am = readAlignmentMask(mdata);
  assert(checkAlignment(mdata));              //0x2A

  ret.numHands = readWord(mdata);
  
  cout << "Number of hands: " << ret.numHands << endl;

  ret.itemClass = readItemClass(mdata);
  assert(checkAlignment(mdata));              //0x32
  ret.statReqs = readStatSet(mdata);
  assert(checkAlignment(mdata));              //0x40
  ret.statMods = readStatSet(mdata);
  ret.cm = readCurseMask(mdata);
  ret.spellLevel = readWord(mdata);
  ret.classRestricted = readWord(mdata) != 0;
  //end of record, read to end of alignment
  seekTo(mdata, RECORD_SIZE);
  return ret;
}

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

  ifstream mdata(datAbsolutePath, ios::binary | ios::in);

  //read what I think is the header out
  char *version = readVBString(&mdata);

  seekTo(&mdata, 0x177);
 
  for(int i = 0; i <= NUM_RECORDS; i++){
    cout << "Reading item " << i << endl;
    readItem(&mdata);
  }
 
  return 0;
}
