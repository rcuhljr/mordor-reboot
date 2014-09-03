#ifndef GUILD_H
#define GUILD_H

#include <QList>
#include <QString>

struct GUILD
{
    QString name;
    QList<int> requirements;
    QList<bool> alignments;

    GUILD(QString name, QList<int> reqs, QList<bool> align)
    {
        this->name = name;
        requirements = reqs;
        alignments = align;
    }
};

#endif // GUILD_H
