
#include <iostream>
#include <fstream>
#include <assert.h>

#include "mordorBinaryReader.hpp"
#include "mdataTools.hpp"
#include "readMData2.hpp"

using namespace std;

const int RECORD_SIZE = 75;

struct header{
  char* version;
  WORD numSpells;
};

struct header readHeader(ifstream *mdata){
  header ret;
  ret.version = readVBString(mdata);
  seekTo(mdata,RECORD_SIZE);
  ret.numSpells = readWord(mdata);
  seekTo(mdata,RECORD_SIZE);
  return ret;
}

struct Spell readSpell(ifstream *mdata){
  struct Spell thisSpell;
  thisSpell.name = readVBString(mdata);
  thisSpell.id = readWord(mdata);
  thisSpell.spellClass = readWord(mdata);
  thisSpell.level = readWord(mdata);
  thisSpell.u4 = readWord(mdata);
  assert(checkByteAlignment(mdata));
  thisSpell.killEffect = readWord(mdata);
  thisSpell.affectMonster = readWord(mdata);
  thisSpell.affectGroup = readWord(mdata);
  thisSpell.damage1 = readWord(mdata);
  thisSpell.damage2 = readWord(mdata);
  thisSpell.specialEffect = readWord(mdata);
  thisSpell.required = readWord(mdata);
  thisSpell.resistedBy = readWord(mdata);
  return thisSpell;
}

void printSpell(struct Spell *s){
  cout << s->name << endl;
  cout << "ID:\t\t\t" << s->id << endl;
  cout << "Class:\t\t\t" << s->spellClass << endl;
  cout << "Level:\t\t\t" << s->level << endl;
  cout << "U4:\t\t\t" << s->u4 << endl;
  cout << "KillEffect:\t\t" << s->killEffect << endl;
  cout << "Affect Monster:\t\t" << s->affectMonster << endl;
  cout << "Affect Group:\t\t" << s->affectGroup << endl;
  cout << "damage1:\t\t" << s->damage1 << endl;
  cout << "damage2:\t\t" << s->damage2 << endl;
  cout << "SpecialEffect:\t\t" << s->specialEffect << endl;
  cout << "Required:\t\t" << s->required << endl;
  cout << "Resisted By:\t\t" << s->resistedBy << endl;
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

  ifstream mdata_input(datAbsolutePath, ios::binary | ios::in);

  // read file version, vb string
  header info = readHeader(&mdata_input);

  cout << "Version " << info.version << endl;

  // read spell list
  for(int i = 0; i < info.numSpells; i++){
    cout << "Reading spell " << dec << i << endl;
    struct Spell first = readSpell(&mdata_input);
    printSpell(&first);
    cout << endl;
    seekTo(&mdata_input,RECORD_SIZE);
  }

  /*
  mdata_input.seekg(0x00001f80);
  for(int i = 0; i < numSpells2; i++){
    cout << "Reading spell " << i << endl;
    spell first = readSpell(&mdata_input);
    printSpell(&first);
    cout << endl;
    seekTo(&mdata_input,RECORD_SIZE);
  }
  */
  return 0;
}
