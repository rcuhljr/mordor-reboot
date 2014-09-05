#ifndef CREATION_LOGIC_H
#define CREATION_LOGIC_H

#include "guild.h"
#include "race.h"
#include <QList>

class CreationLogic
{
public:
    CreationLogic();
    virtual ~CreationLogic();

    const QList<RACE> GetRaces() const;

private:
    QList<RACE> Races;
};

#endif // CREATION_LOGIC_H
