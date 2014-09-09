#include "race.h"
#include "guild.h"
#include <QJsonArray>

Race::Race()
    : Alignments()
    , BonusPoints()
    , ExpFactor()
    , MaxAge()
    , MaxStats()
    , MinStats()
    , Name()
    , Resistances()
    , Size()
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

    BonusPoints = json["bonus_points"].toInt();

    ExpFactor = json["exp_factor"].toInt();

    MaxAge = json["max_age"].toInt();

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

    QJsonArray resistancesArray = json["resistances"].toArray();
    foreach (const QJsonValue& v, resistancesArray)
    {
        Resistances << v.toInt();
    }

    Size = json["size"].toInt();
}
