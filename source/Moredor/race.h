#ifndef RACE_H
#define RACE_H

#include <QList>
#include <QObject>
#include <QString>

class Guild;

class Race
{
public:
    Race();
    Race(QString name, QList<bool> align, QList<int> startStats, QList<int> max, int startPoints);
    virtual ~Race();

    QString Name;
    QList<bool> Alignments;
    QList<int> StartingStats;
    QList<int> MaxStats;
    int StartingPoints;
    QList<Guild> Guilds;
};

Q_DECLARE_METATYPE(Race)

#endif // RACE_H
