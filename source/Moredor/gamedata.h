#ifndef CREATION_LOGIC_H
#define CREATION_LOGIC_H

#include "guild.h"
#include "race.h"
#include <QList>

class GameData
{
public:
    GameData();
    virtual ~GameData();

    const QList<Race> GetRaces() const;

private:
    QList<Race> Races;
    QList<Guild> Guilds;
};

#endif // CREATION_LOGIC_H
