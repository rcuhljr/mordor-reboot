#ifndef GUILD_H
#define GUILD_H

#include <vector>
#include <QString>

struct GUILD
{
    QString name;
    std::vector<int> requirements;
    std::vector<bool> alignments;

    GUILD(QString name, int *reqs, bool *align)
    {
        this->name = name;
        requirements = std::vector<int>(reqs, reqs + sizeof(reqs)/sizeof(int) );
        alignments = std::vector<bool>(align, align + sizeof(align)/sizeof(bool) );
    }
};

#endif // GUILD_H
