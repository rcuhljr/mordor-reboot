#ifndef RACE_H
#define RACE_H

#include "guild.h"
#include <vector>
#include <QList>
#include <QString>

struct RACE {
    QString name;
    std::vector<bool> alignments;
    std::vector<int> startingStats;
    std::vector<int> maxStats;
    QList<GUILD> guilds;

    RACE(QString name, bool *align, int *start, int *max){
        this->name = name;
        alignments = std::vector<bool>(align, align + sizeof(align)/sizeof(bool) );
        startingStats = std::vector<int>(start, start + sizeof(start)/sizeof(int) );
        maxStats = std::vector<int>(max, max + sizeof(max)/sizeof(int) );
    }
};

#endif // RACE_H
