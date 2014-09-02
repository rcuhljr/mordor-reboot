#ifndef CREATIONLOGIC_H
#define CREATIONLOGIC_H

#include "guild.h"
#include "race.h"
#include <QObject>
#include <QStringList>
#include <QMap>
#include <QString>

class CreationLogic
{
public:
    enum Alignments {Good = 0, Neutral, Evil};
    enum Stats {STR = 0,INT,WIS,CON,CHA,DEX};

    CreationLogic();
    virtual ~CreationLogic() {}
    const QList<RACE> getRaces() const;

private:
    QList<RACE> races;
};

Q_DECLARE_METATYPE(CreationLogic::Alignments)

#endif // CREATIONLOGIC_H
