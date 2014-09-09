#include "guild.h"

Guild::Guild(QString name, QList<int> reqs, QList<bool> align)
{
    Name = name;
    RequiredStats = reqs;
    Alignments = align;
}

Guild::~Guild()
{
}
