#ifndef CREATION_LOGIC_H
#define CREATION_LOGIC_H

#include "guild.h"
#include "race.h"
#include <QList>
#include <QObject>

class CreationLogic
{
public:
    enum Alignments {Good = 0, Neutral, Evil};
    enum Stats {STR = 0, INT, WIS, CON, CHA, DEX};

    CreationLogic();
    virtual ~CreationLogic();

    const QList<RACE> GetRaces() const;

private:
    QList<RACE> Races;
};

Q_DECLARE_METATYPE(CreationLogic::Alignments)

#endif // CREATION_LOGIC_H
