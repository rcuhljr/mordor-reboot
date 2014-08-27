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

    GUILD* nomad = new GUILD(nomadStats, nomadAlign);
    GUILD* warrior = new GUILD(warriorStats, warriorAlign);
    GUILD* thief = new GUILD(thiefStats, thiefAlign);

    nomad->name = QString("Nomad");
    warrior->name = QString("Warrior");
    thief->name = QString("Thief");


    int humanStart[6] = {4,4,4,6,5,6};
    int humanMax[6] = {17,18,18,17,18,18};
    bool humanAlign[3] = {true,true,true};


    RACE* human = new RACE(humanAlign, humanStart, humanMax);
    human->name = QString("Human");
    QList<GUILD> humanGuilds;
    humanGuilds.push_back(*nomad);
    humanGuilds.push_back(*warrior);
    humanGuilds.push_back(*thief);
    human->guilds = humanGuilds;

    races[human->name] = *human;

    int giantStart[6] = {12,4,3,9,2,3};
    int giantMax[6] =  {25,17,17,19,16,18};
    bool giantAlign[3] = {true,true,true};


    RACE* giant = new RACE(giantAlign, giantStart, giantMax);
    giant->name = QString("Giant");
    QList<GUILD> giantGuilds;
    giantGuilds.push_back(*nomad);
    giantGuilds.push_back(*warrior);
    giant->guilds = giantGuilds;

    races[giant->name] = *giant;
}


QStringList CreationLogic::availableRaces(){
    QStringList raceStrings;
    QMap<QString,RACE>::const_iterator i = races.constBegin();
    while(i != races.constEnd()){
        raceStrings.push_back(i.key());
        i++;
    }
    return raceStrings;
}
