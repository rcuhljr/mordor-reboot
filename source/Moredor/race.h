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
    int StartingPoints;
    QList<GUILD> Guilds;

    RACE() {}
    RACE(QString name, QList<bool> align, QList<int> startStats, QList<int> max, int startPoints)
    {
        Name = name;
        Alignments = align;
        StartingStats = startStats;
        MaxStats = max;
        StartingPoints = startPoints;
    }
};

Q_DECLARE_METATYPE(RACE)

#endif // RACE_H
