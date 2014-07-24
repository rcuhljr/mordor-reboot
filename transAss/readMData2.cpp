
#include <iostream>
#include <fstream>
#include <assert.h>

#include "mordorBinaryReader.hpp"
#include "mdataTools.hpp"
#include "readMData2.hpp"

using namespace std;

const int RECORD_SIZE = 75;

struct spell{
  char* name;
  int id;
  int spellClass;
  int level;
  int u4;
  int killEffect;
  int affectMonster;
  int affectGroup;
  int damage1;
  int damage2;
  int specialEffect;
  int required;
  int resistedBy;
};

spell readSpell(ifstream *mdata){
  spell thisSpell;
  thisSpell.name = readVBString(mdata);
  thisSpell.id = readByte(mdata);
  thisSpell.spellClass = readByte(mdata);
  thisSpell.level = readByte(mdata);
  thisSpell.u4 = readByte(mdata);
  BYTE b = readByte(mdata);
  assert(b == 0);
  thisSpell.killEffect = readByte(mdata);
  thisSpell.affectMonster = readByte(mdata);
  thisSpell.affectGroup = readByte(mdata);
  thisSpell.damage1 = readByte(mdata);
  thisSpell.damage2 = readByte(mdata);
  thisSpell.specialEffect = readByte(mdata);
  thisSpell.required = readByte(mdata);
  thisSpell.resistedBy = readByte(mdata);
  return thisSpell;
}

void printSpell(spell *s){
  cout << s->name << endl;
  //flesh this out1
}

int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << "Expected exactly one argument -- the absolute path to the MDAT12.MDR" << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (not possiblyValidFile(datAbsolutePath, MDATA2)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA2.MDR" << endl;
    return 1;
  }

  // read file version, vb string
  // read number of spells as record 2
  // read number of spells as record 3
  // read spell list
  

  return 0;
}
