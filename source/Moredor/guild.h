#ifndef GUILD_H
#define GUILD_H

#include <QJsonObject>
#include <QList>
#include <QString>

class Guild
{
public:
    Guild(QString name, QList<int> reqs, QList<bool> align);
    virtual ~Guild();

    QString Name;
    QList<int> RequiredStats;
    QList<bool> Alignments;
};

#endif // GUILD_H
