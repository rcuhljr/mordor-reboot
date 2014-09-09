#include "race.h"
#include "guild.h"
#include <QJsonArray>

Race::Race()
    : Alignments()
    , StartingPoints()
    , MaxStats()
    , MinStats()
    , Name()
    , Guilds()
{
}

Race::~Race()
{
}

void Race::Read(const QJsonObject& json)
{
    QJsonArray alignmentArray = json["alignment"].toArray();
    foreach (const QJsonValue& v, alignmentArray)
    {
        Alignments << v.toBool();
    }

    StartingPoints = json["bonus_points"].toInt();

//    "exp_factor": 5,

//    "max_age": 275,

    QJsonArray maxStatsArray = json["max_stats"].toArray();
    foreach (const QJsonValue& v, maxStatsArray)
    {
        MaxStats << v.toInt();
    }

    QJsonArray minStatsArray = json["min_stats"].toArray();
    foreach (const QJsonValue& v, minStatsArray)
    {
        MinStats << v.toInt();
    }

    Name = json["name"].toString();

//    "resistances": [
//        45,
//        80,
//        0,
//        0,
//        50,
//        50,
//        0,
//        40,
//        50,
//        90,
//        0
//    ],

//    "size": 1
}
