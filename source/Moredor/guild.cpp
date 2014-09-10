#include "guild.h"
#include <QJsonArray>

Guild::Guild()
    : AbilityRates()
    , AdCap()
    , AdGain()
    , Alignments()
    , AttackInc()
    , AverageHits()
    , BaseMagic()
    , CapMagic()
    , DefenseInc()
    , ExpFactor()
    , GoldRatio()
    , LevelMod()
    , MaxHitpoints()
    , MaxLevel()
    , Name()
    , QuestPercentage()
    , Races()
    , RequiredStats()
{
}

Guild::~Guild()
{
}

void Guild::Read(const QJsonObject& json)
{
    QJsonArray abilityRatesArray = json["ability_rates"].toArray();
    foreach (const QJsonValue& v, abilityRatesArray)
    {
        AbilityRates << v.toDouble();
    }

    AdCap = json["ad_cap"].toInt();

    AdGain = json["ad_gain"].toDouble();

    QJsonArray alignmentArray = json["alignment"].toArray();
    foreach (const QJsonValue& v, alignmentArray)
    {
        Alignments << v.toBool();
    }

    AttackInc = json["attack_inc"].toDouble();

    AverageHits = json["average_hits"].toInt();

    QJsonArray baseMagicArray = json["base_magic"].toArray();
    foreach (const QJsonValue& v, baseMagicArray)
    {
        BaseMagic << v.toDouble();
    }

    QJsonArray capMagicArray = json["cap_magic"].toArray();
    foreach (const QJsonValue& v, capMagicArray)
    {
        CapMagic << v.toInt();
    }

    DefenseInc = json["defense_inc"].toDouble();

    ExpFactor = json["exp_factor"].toInt();

    GoldRatio = json["gold_ratio"].toInt();

    LevelMod = json["level_mod"].toDouble();

    MaxHitpoints = json["max_hitpoints"].toInt();

    MaxLevel = json["max_level"].toInt();

    Name = json["name"].toString();

    QuestPercentage = json["quest_percentage"].toInt();

    QJsonArray racesArray = json["races"].toArray();
    foreach (const QJsonValue& v, racesArray)
    {
        Races << v.toBool();
    }

    QJsonArray requiredStatsArray = json["required_stats"].toArray();
    foreach (const QJsonValue& v, requiredStatsArray)
    {
        RequiredStats << v.toInt();
    }
}
