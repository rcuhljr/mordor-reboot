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

        GUILD(QString name, int *reqs, bool *align){
            this->name = name;
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

        RACE(QString name, bool *align, int *start, int *max){
            this->name = name;
            alignments = std::vector<bool>(align, align + sizeof(align)/sizeof(bool) );
            startingStats = std::vector<int>(start, start + sizeof(start)/sizeof(int) );
            maxStats = std::vector<int>(max, max + sizeof(max)/sizeof(int) );

        }
    };

    CreationLogic();
    virtual ~CreationLogic() {}
    QStringList availableRaces();
    QStringList getGuilds(int raceIndex);

private:
    QList<RACE*> races;
};

#endif // CREATIONLOGIC_H
