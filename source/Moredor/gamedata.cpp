#include "gamedata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <QtDebug>

GameData::GameData()
    : Races()
{
    // The root directory for this check is the directory of the executable

    if (!QFile::exists("assets/races.json"))
    {
        qWarning("Couldn't find races file.");
        return;
    }

    QFile racesFile("assets/races.json");
    if (!racesFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open races file.");
        qWarning() << static_cast<int>(racesFile.error());
        return;
    }
    QByteArray racesData = racesFile.readAll();
    QJsonDocument racesDoc(QJsonDocument::fromJson(racesData));
    QJsonObject racesObject = racesDoc.object();

    // Import races in the order defined here so that they will be in the
    // same order as the allowed races for each guild
    QJsonArray raceNameArray = racesObject["race_names"].toArray();
    foreach(const QJsonValue& v, raceNameArray)
    {
        QJsonObject raceObject = racesObject[v.toString()].toObject();
        Race race;
        race.Read(raceObject);
        Races << race;
    }

    // The root directory for this check is the directory of the executable
    QFile guildsFile("assets/guilds.json");
    if (!guildsFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open guilds file.");
        return;
    }
    QByteArray guildsData = guildsFile.readAll();
    QJsonDocument guildsDoc(QJsonDocument::fromJson(guildsData));
    QJsonObject guildsObject = guildsDoc.object();
    foreach(const QJsonValue& v, guildsObject)
    {
        Guild guild;
        guild.Read(v.toObject());
        Guilds << guild;

        for(int i = 0; i < guild.Races.count(); ++i)
        {
            if(guild.Races[i])
            {
                Races[i].Guilds << guild;
            }
        }
    }
}

GameData::~GameData()
{
}

const QList<Race> GameData::GetRaces() const
{
    return Races;
}
