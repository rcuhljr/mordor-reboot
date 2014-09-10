#include "creationlogic.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>

CreationLogic::CreationLogic()
    : Races()
{
    // The root directory for this check is the directory of the executable
    QFile racesFile(":/races");
    if (!racesFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open races file.");
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
    QFile guildsFile(":/guilds");
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

CreationLogic::~CreationLogic()
{
}

const QList<Race> CreationLogic::GetRaces() const
{
    return Races;
}
