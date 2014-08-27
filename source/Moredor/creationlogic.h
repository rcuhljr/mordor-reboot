#ifndef CREATIONLOGIC_H
#define CREATIONLOGIC_H
#include <QStringList>
#include <QMap>
#include <QString>

class CreationLogic
{
public:
    enum Alignments {Good, Neutral, Evil};
    enum Stats {STR,INT,WIS,CON,CHA,DEX};

    struct GUILD {
        QString name;
        std::vector<int> requirements;
        std::vector<bool> alignments;

        GUILD(int *reqs, bool *align){
            requirements = std::vector<int>(reqs, reqs + sizeof(reqs)/sizeof(int) );
            alignments = std::vector<bool>(align, align + sizeof(align)/sizeof(bool) );
        }
    };

    struct RACE {
        QString name;
        std::vector<bool> alignments;
        std::vector<int> startingStats;
        std::vector<int> maxStats;
        QList<GUILD> guilds;

        RACE(bool *align, int *start, int *max){
            alignments = std::vector<bool>(align, align + sizeof(align)/sizeof(bool) );
            startingStats = std::vector<int>(start, start + sizeof(start)/sizeof(int) );
            maxStats = std::vector<int>(max, max + sizeof(max)/sizeof(int) );

        }

        RACE(){}
    };
    CreationLogic();
    QStringList availableRaces();

private:
    QMap<QString,RACE> races;
};

#endif // CREATIONLOGIC_H
