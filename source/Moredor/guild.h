#ifndef GUILD_H
#define GUILD_H

#include <QJsonObject>
#include <QList>
#include <QString>

class Guild
{
public:
    Guild();
    virtual ~Guild();

    void Read(const QJsonObject& json);

    QList<double> AbilityRates;
    int AdCap;
    double AdGain;
    QList<bool> Alignments;
    double AttackInc;
    int AverageHits;
    QList<double> BaseMagic;
    QList<int> CapMagic;
    double DefenseInc;
    int ExpFactor;
    int GoldRatio;
    double LevelMod;
    int MaxHitpoints;
    int MaxLevel;
    QString Name;
    int QuestPercentage;
    QList<bool> Races;
    QList<int> RequiredStats;
};

#endif // GUILD_H
