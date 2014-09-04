#ifndef GUILD_H
#define GUILD_H

#include <QList>
#include <QString>

struct GUILD
{
    QString Name;
    QList<int> RequiredStats;
    QList<bool> Alignments;

    GUILD(QString name, QList<int> reqs, QList<bool> align)
    {
        this->Name = name;
        RequiredStats = reqs;
        Alignments = align;
    }
};

#endif // GUILD_H
