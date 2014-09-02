#include "creationlogic.h"
#include <QStringList>
#include <Qmap>
#include <QList>

CreationLogic::CreationLogic()
{
    //#TODO Read data from Json
    int nomadStats[6] = {1,1,1,1,1,1};
    bool nomadAlign[3] = {true,true,true};

    int warriorStats[6] = {14,7,5,10,3,8};
    bool warriorAlign[3] = {true,true,true};

    int thiefStats[6] = {8,12,8,6,5,17};
    bool thiefAlign[3] = {false,true,false};

    GUILD* nomad = new GUILD("Nomad", nomadStats, nomadAlign);
    GUILD* warrior = new GUILD("Warrior", warriorStats, warriorAlign);
    GUILD* thief = new GUILD("Thief", thiefStats, thiefAlign);

    int humanStart[6] = {4,4,4,6,5,6};
    int humanMax[6] = {17,18,18,17,18,18};
    bool humanAlign[3] = {true,true,true};

    RACE* human = new RACE("Human", humanAlign, humanStart, humanMax);
    QList<GUILD> humanGuilds;
    humanGuilds << *nomad << *warrior << *thief;
    human->guilds = humanGuilds;

    races << human;


    int giantStart[6] = {12,4,3,9,2,3};
    int giantMax[6] =  {25,17,17,19,16,18};
    bool giantAlign[3] = {true,true,true};

    RACE* giant = new RACE("Giant", giantAlign, giantStart, giantMax);
    QList<GUILD> giantGuilds;
    giantGuilds << *nomad << *warrior;
    giant->guilds = giantGuilds;

    races << giant;
}

QStringList CreationLogic::availableRaces()
{
    QStringList raceStrings;
    foreach(const RACE* race, races)
    {
        raceStrings << race->name;
    }
    return raceStrings;
}

QStringList CreationLogic::getGuilds(int raceIndex)
{
    QStringList guildStrings;
    foreach(const GUILD guild, races[raceIndex]->guilds)
    {
        guildStrings << guild.name;
    }
    return guildStrings;
}
