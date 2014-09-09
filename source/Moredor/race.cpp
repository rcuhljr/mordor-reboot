#include "race.h"
#include "guild.h"

Race::Race()
{
}

Race::Race(QString name, QList<bool> align, QList<int> startStats, QList<int> max, int startPoints)
{
    Name = name;
    Alignments = align;
    StartingStats = startStats;
    MaxStats = max;
    StartingPoints = startPoints;
}

Race::~Race()
{
}
