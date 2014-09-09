#include "race.h"
#include "guild.h"

Race::Race()
{
}

Race::Race(QString name, QList<bool> align, QList<int> startStats, QList<int> max, int startPoints)
{
    Name = name;
    Alignments = align;
    StartingStats = startStats;
    MaxStats = max;
    StartingPoints = startPoints;
}

Race::~Race()
{
}

void Race::Read(const QJsonObject& json)
{
    Name = json["name"].toString();
    //qWarning(Name.toLatin1());
    StartingPoints = json["bonus_points"].toInt();
    //qWarning(QString("%1").arg(StartingPoints).toLatin1());

    // Example:
//    "alignment": [
//        false,
//        true,
//        false
//    ],
//    "bonus_points": 10,
//    "exp_factor": 5,
//    "max_age": 275,
//    "max_stats": [
//        18,
//        18,
//        19,
//        19,
//        17,
//        18
//    ],
//    "min_stats": [
//        3,
//        3,
//        7,
//        3,
//        3,
//        5
//    ],
//    "name": "Dwarf",
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
