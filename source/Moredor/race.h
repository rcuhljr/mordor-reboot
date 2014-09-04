#ifndef RACE_H
#define RACE_H

#include "guild.h"
#include <QList>
#include <QObject>
#include <QString>

struct RACE
{
    QString Name;
    QList<bool> Alignments;
    QList<int> StartingStats;
    QList<int> MaxStats;
    QList<GUILD> Guilds;

    RACE() {}
    RACE(QString name, QList<bool> align, QList<int> start, QList<int> max)
    {
        Name = name;
        Alignments = align;
        StartingStats = start;
        MaxStats = max;
    }
};

Q_DECLARE_METATYPE(RACE)

#endif // RACE_H
