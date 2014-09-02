#ifndef RACE_H
#define RACE_H

#include "guild.h"
#include <vector>
#include <QList>
#include <QObject>
#include <QString>

struct RACE
{
    QString name;
    QList<bool> alignments;
    QList<int> startingStats;
    QList<int> maxStats;
    QList<GUILD> guilds;

    RACE() {}
    RACE(QString name, QList<bool> align, QList<int> start, QList<int> max)
    {
        this->name = name;
        alignments = align;
        startingStats = start;
        maxStats = max;
    }
};

Q_DECLARE_METATYPE(RACE)

#endif // RACE_H
