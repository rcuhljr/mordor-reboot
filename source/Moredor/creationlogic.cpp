#include "creationlogic.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>

CreationLogic::CreationLogic()
    : Races()
{
    // The root directory for this check is the directory of the executable
    QFile racesFile("assets/races.json");
    if (!racesFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open races file.");
        return;
    }
    QByteArray racesData = racesFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(racesData));
    QJsonObject rootObject = loadDoc.object();

    QJsonArray raceNameArray = rootObject["race_names"].toArray();
    foreach(const QJsonValue& v, raceNameArray)
    {
        QJsonObject raceObject = rootObject[v.toString()].toObject();
        Race race;
        race.Read(raceObject);
        Races << race;
    }



    // The root directory for this check is the directory of the executable
//    QFile guildsFile("assets/guilds.json");
//    if (!guildsFile.open(QIODevice::ReadOnly))
//    {
//        qWarning("Couldn't open guilds file.");
//        return;
//    }



//    QList<int> nomadStats = QList<int>() << 1 << 1 << 1 << 1 << 1 << 1;
//    QList<bool> nomadAlign = QList<bool>() << true << true << true;

//    QList<int> warriorStats = QList<int>() << 14 << 7 << 5 << 10 << 3 << 8;
//    QList<bool> warriorAlign = QList<bool>() << true << true << true;

//    QList<int> thiefStats = QList<int>() << 8 << 12 << 8 << 6 << 5 << 17;
//    QList<bool> thiefAlign = QList<bool>() << false << true << false;

//    Guild nomad("Nomad", nomadStats, nomadAlign);
//    Guild warrior("Warrior", warriorStats, warriorAlign);
//    Guild thief("Thief", thiefStats, thiefAlign);

//    QList<bool> humanAlign = QList<bool>() << true << true << true;
//    QList<int> humanStart = QList<int>() << 4 << 4 << 4 << 6 << 5 << 6;
//    QList<int> humanMax = QList<int>() << 17 << 18 << 18 << 17 << 18 << 18;

//    Race human("Human", humanAlign, humanStart, humanMax, 7);
//    QList<Guild> humanGuilds;
//    humanGuilds << nomad << warrior << thief;
//    human.Guilds = humanGuilds;

//    Races << human;


//    QList<bool> giantAlign = QList<bool>() << false << true << false;
//    QList<int> giantStart = QList<int>() << 12 << 4 << 3 << 9 << 2 << 3;
//    QList<int> giantMax =  QList<int>() << 25 << 17 << 17 << 19 << 16 << 18;

//    Race giant("Giant", giantAlign, giantStart, giantMax, 5);
//    QList<Guild> giantGuilds;
//    giantGuilds << nomad << warrior;
//    giant.Guilds = giantGuilds;

//    Races << giant;


//    // TODO: Remove this, it is only for alignment testing
//    QList<bool> drowAlign = QList<bool>() << false << false << true;
//    Race drow("Drow", drowAlign, humanStart, humanMax, 4);
//    drow.Guilds = humanGuilds;

//    Races << drow;
}

CreationLogic::~CreationLogic()
{
}

const QList<Race> CreationLogic::GetRaces() const
{
    return Races;
}
