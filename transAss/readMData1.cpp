#include <iostream>
#include <fstream>
#include "mdataTools.hpp"
#include "mordorBinaryReader.hpp"
#include "readMData1.hpp"
#include "assert.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using namespace std;

const int RECORD_LENGTH = 260;

struct header{
  char* version;
  WORD numRaces;
  WORD numGuilds;
  WORD numItemSubtypes;
  WORD numItemTypes;
  WORD numMonsterSubtypes;
  WORD numMonsterTypes;
};

void printFileHeader(header *ret){
  cout << "Version:              " << ret->version << endl
       << "Num Races:            " << ret->numRaces << endl
       << "Num Guilds:           " << ret->numGuilds << endl
       << "Num Item Subtypes:    " << ret->numItemSubtypes << endl
       << "Num Item Types:       " << ret->numItemTypes << endl
       << "Num Monster Subtypes: " << ret->numMonsterSubtypes << endl
       << "Num Monster Types:    " << ret->numMonsterTypes << endl;
}

header readFileHeader(ifstream *mdata){
  header ret;

  ret.version = readVBString(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numRaces = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numGuilds = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numItemSubtypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numItemTypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numMonsterSubtypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  ret.numMonsterTypes = readWord(mdata);
  seekTo(mdata, RECORD_LENGTH);
  printFileHeader(&ret);
  return ret;
}

void printRace(race *ret){
  cout << ret->name << endl
       << "Min Stats: ";

  for(int i = 0; i < 6; i++){
    cout << ret->minStats[i] << " ";
  }
  cout << endl
       << "Max Stats: ";
  for(int i = 0; i < 6; i++){
    cout << ret->maxStats[i] << " ";
  }
  cout << endl << "Resistances: ";
  for(int i = 0; i < 11; i++){
    cout << ret->resistances[i] << " ";
  }
  cout << endl
       << "Alignment: " << ret->alignment << endl
       << "Size: " << ret->size << endl
       << "Bonus Points: " << ret->bonusPoints << endl
       << "Max Age: " << ret->maxAge << endl
       << "expFactor: " << ret->expFactor << endl;
}

QJsonObject raceToJson(race *r){
    QJsonObject ret;
    ret["name"] = QJsonValue(r->name);
    QJsonArray minstats;
    QJsonArray maxstats;
    for(int i = 0; i < 6; i++){
      minstats.append(QJsonValue(r->minStats[i]));
      maxstats.append(QJsonValue(r->maxStats[i]));
    }
    ret["min_stats"] = minstats;
    ret["max_stats"] = maxstats;

    QJsonArray resistances;
    for(int i = 0; i < 11; i++){
      resistances.append(QJsonValue(r->resistances[i]));
    }
    ret["resistances"] = resistances;

    ret["alignment"] = QJsonValue(r->alignment);
    ret["size"] = QJsonValue(r->size);
    ret["bonus_points"] = QJsonValue(r->bonusPoints);
    ret["max_age"] = QJsonValue(r->maxAge);
    ret["exp_factor"] = QJsonValue(r->expFactor);

    return ret;
}

race readRace(ifstream *mdata){
  race ret;
  ret.name = readVBString(mdata);
  for(int i = 0; i < 6; i++){
    ret.minStats[i] = readWord(mdata);
  }
  readWord(mdata);
  for(int i = 0; i < 6; i++){
    ret.maxStats[i] = readWord(mdata);
  }
  readWord(mdata);
  for(int i = 0; i < 11; i++){
    ret.resistances[i] = readWord(mdata);
  }
  readWord(mdata);
  ret.alignment = readWord(mdata);
  readWord(mdata);
  ret.size = readWord(mdata);
  ret.bonusPoints = readWord(mdata);
  ret.maxAge = readWord(mdata);
  ret.expFactor = readFloat(mdata);

  printRace(&ret);
  seekTo(mdata, RECORD_LENGTH);
  return ret;
}

void printGuild(guild *ret){
  cout << ret->name << endl
       << "Avg. Hits: " << ret->averageHits << endl
       << "Max Level: " << ret->maxLevel << endl
       << "MH: " << ret->MH << endl
       << "EXP Factor: " << ret->expFactor << endl
       << "reqStats: ";
  for(int i = 0; i < 6; i++){
    cout << ret->reqStats[i] << " ";
  }
  cout << endl
       << "alignment: " << ret->alignment << endl
       << "ability rates: ";
  for(int i = 0; i < 6; i++){
    cout << ret->abilityRates[i] << " ";
  }
  cout << endl
       << "questPercentage: " << ret->questPercentage << endl
       << "baseMagics: ";
  for(int i = 0; i < 18; i++){
    cout << ret->baseMagics[i] << " ";
  }
  cout << endl
       << "capMagics: ";
  for(int i = 0; i < 18; i++){
    cout << ret->capMagics[i] << " ";
  }
  cout << endl
       << "raceMask: " << ret->raceMask << endl
       << "GoldRatio: " << ret->goldRatio<< endl
       << "levelMod: " << ret->levelMod << endl
       << "Attack Increment: " << ret->attackIncrement << endl
       << "Defense Increment: " << ret->defIncrement << endl
       << "AD Cap: " << ret->aDCap << endl
       << "AD Gain: " << ret->aDGain << endl
       << "u3: " << ret->u3 << endl
       << "u7: " << ret->u7 << endl
       << "u8: " << ret->u8 << endl
       << "u16: " << ret->u16 << endl
       << "u17: " << ret->u17 << endl;
}

QJsonObject guildToJson(guild *g){
    QJsonObject ret;
    ret["name"] = QJsonValue(g->name);
    ret["average_hits"] = QJsonValue(g->averageHits);
    ret["max_level"] = QJsonValue(g->maxLevel);
    ret["max_hitpoints"] = QJsonValue(g->MH);
    ret["exp_factor"] = QJsonValue(g->expFactor);
    ret["alignment"] = QJsonValue(g->alignment);
    ret["quest_percentage"] = QJsonValue(g->questPercentage);
    ret["race_mask"] = QJsonValue(g->raceMask);
    ret["gold_ratio"] = QJsonValue(g->goldRatio);
    ret["level_mod"] = QJsonValue(g->levelMod);
    ret["attack_inc"] = QJsonValue(g->attackIncrement);
    ret["defense_inc"] = QJsonValue(g->defIncrement);
    ret["ad_cap"] = QJsonValue(g->aDCap);
    ret["ad_gain"] = QJsonValue(g->aDGain);

    QJsonArray reqStats;
    QJsonArray abilityRates;
    for(int i = 0; i < 6; i++){
      reqStats.append(QJsonValue(g->reqStats[i]));
      abilityRates.append(QJsonValue(g->abilityRates[i]));
    }
    ret["required_stats"] = reqStats;
    ret["ability_rates"] = abilityRates;

    QJsonArray baseMagic;
    QJsonArray capMagic;
    for(int i = 0; i < 18; i++){
      baseMagic.append(QJsonValue(g->baseMagics[i]));
      capMagic.append(QJsonValue(g->capMagics[i]));
    }
    ret["base_magic"] = baseMagic;
    ret["cap_magic"] = capMagic;

    return ret;
}

guild readGuild(ifstream *mdata){
  guild ret;

  ret.name = readVBString(mdata);
  ret.averageHits = readWord(mdata);
  ret.maxLevel = readWord(mdata);
  ret.MH = readWord(mdata);
  ret.expFactor = readFloat(mdata);
  ret.u3 = readWord(mdata);
  for(int i = 0; i < 6; i++){
    ret.reqStats[i] = readWord(mdata);
  }
  readWord(mdata); // dead data?
  ret.alignment = readWord(mdata);
  readWord(mdata); // dead data?
  for(int i = 0; i < 6; i++){
    ret.abilityRates[i] = readFloat(mdata);
  }
  ret.u7 = readWord(mdata);
  ret.u8 = readFloat(mdata);
  readFloat(mdata); //dead data?
  ret.questPercentage = readWord(mdata);
  for(int i = 0; i < 18; i++){
    ret.baseMagics[i] = readFloat(mdata);
  }
  readFloat(mdata); // dead data?
  for(int i = 0; i < 18; i++){
    ret.capMagics[i] = readFloat(mdata);
  }
  readWord(mdata); // dead data?
  readWord(mdata); // dead data?
  ret.raceMask = readWord(mdata);
  readWord(mdata); // dead data?
  ret.goldRatio = readWord(mdata);
  ret.levelMod = readFloat(mdata);
  ret.attackIncrement = readFloat(mdata);
  ret.defIncrement = readFloat(mdata);
  ret.aDCap = readWord(mdata);
  ret.aDGain = readFloat(mdata);
  ret.u16 = readWord(mdata);
  ret.u17 = readWord(mdata);

  printGuild(&ret);
  seekTo(mdata, RECORD_LENGTH);
  /* Some of the u* values are non 0.

  assert(0 == ret.u3);
  assert(0 == ret.u7);
  assert(0 == ret.u8);
  assert(0 == ret.u12);
  assert(0 == ret.u13);
  assert(0 == ret.u14);
  assert(0 == ret.u15);
  assert(0 == ret.u16);
  assert(0 == ret.u17);
  */
  return ret;
}

void printNamedType(namedTypeID *ret){
  cout << dec << ret->name << "\tID: " << ret->type << endl;
}

namedTypeID readNamedType(ifstream *mdata){
  namedTypeID ret;
  ret.name = readVBString(mdata);
  ret.type = readWord(mdata);
  printNamedType(&ret);
  seekTo(mdata, RECORD_LENGTH);
  return ret;
}


int main(int argc, char** argv){
  char* datAbsolutePath;

  if(argc != 2){
    cerr << "Expected exactly one argument -- the absolute path to the MDAT1.MDR"
         << endl;
    return 1;
  }else{
    datAbsolutePath = argv[1];
  }

  if (! possiblyValidFile(datAbsolutePath, MDATA1)){
    cerr << datAbsolutePath << " doesn't appear to be a valid MDATA1.MDR" << endl;
    return 1;
  }

  ifstream mdata(datAbsolutePath, ios::binary | ios::in);

  header h = readFileHeader(&mdata);
  int i = 0;

  cout << endl;
  // races are first
  QJsonObject races;
  for(i = 0; i < h.numRaces; i++){
    race r = readRace(&mdata);
    races[r.name] = raceToJson(&r);
    cout << endl;
  }
  QJsonDocument saveDoc(races);
  QFile saveFile(QStringLiteral("races.json"));
  saveFile.open(QIODevice::WriteOnly);
  saveFile.write(saveDoc.toJson());

  // then guilds
  QJsonObject guilds;
  for(i = 0; i < h.numGuilds; i++){
    guild g = readGuild(&mdata);
    guilds[g.name] = guildToJson(&g);
    cout << endl;
  }

  QJsonDocument saveGuildDoc(guilds);
  QFile saveGuildFile(QStringLiteral("guilds.json"));
  saveGuildFile.open(QIODevice::WriteOnly);
  saveGuildFile.write(saveGuildDoc.toJson());

//  // then item subtypes
//  for(i = 0; i < h.numItemSubtypes; i++){
//    readNamedType(&mdata);
//    cout << endl;
//  }

//  // then items
//  for(i = 0; i < h.numItemTypes; i++){
//    readNamedType(&mdata);
//    cout << endl;
//  }

//  // then monster subtypes
//  for(i = 0; i < h.numMonsterSubtypes; i++){
//    readNamedType(&mdata);
//    cout << endl;
//  }

//  // then monsters
//  for(i = 0; i < h.numMonsterTypes; i++){
//    readNamedType(&mdata);
//    cout << endl;
//  }

  return 0;
}
