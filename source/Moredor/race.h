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
    virtual ~Race();

    void Read(const QJsonObject& json);

    QList<bool> Alignments;
    int StartingPoints;
    QList<int> MaxStats;
    QList<int> MinStats;
    QString Name;
    QList<Guild> Guilds;
};

Q_DECLARE_METATYPE(Race)

#endif // RACE_H
