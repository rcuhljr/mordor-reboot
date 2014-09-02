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

    GUILD nomad("Nomad", nomadStats, nomadAlign);
    GUILD warrior("Warrior", warriorStats, warriorAlign);
    GUILD thief("Thief", thiefStats, thiefAlign);

    QList<bool> humanAlign = QList<bool>() << true << true << true;
    QList<int> humanStart = QList<int>() << 4 << 4 << 4 << 6 << 5 << 6;
    QList<int> humanMax = QList<int>() << 17 << 18 << 18 << 17 << 18 << 18;

    RACE human("Human", humanAlign, humanStart, humanMax);
    QList<GUILD> humanGuilds;
    humanGuilds << nomad << warrior << thief;
    human.guilds = humanGuilds;

    races << human;


    QList<bool> giantAlign = QList<bool>() << true << true << true;
    QList<int> giantStart = QList<int>() << 12 << 4 << 3 << 9 << 2 << 3;
    QList<int> giantMax =  QList<int>() << 25 << 17 << 17 << 19 << 16 << 18;

    RACE giant("Giant", giantAlign, giantStart, giantMax);
    QList<GUILD> giantGuilds;
    giantGuilds << nomad << warrior;
    giant.guilds = giantGuilds;

    races << giant;


    // TODO: Remove this, it is only for alignment testing
    QList<bool> drowAlign = QList<bool>() << false << false << true;
    RACE drow("Drow", drowAlign, humanStart, humanMax);
    drow.guilds = humanGuilds;

    races << drow;
}

const QList<RACE> CreationLogic::getRaces() const
{
    return races;
}
