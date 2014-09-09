#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include "definitions.h"
#include "race.h"
#include <QString>

struct CharacterModel
{
    QString Name;
    Race CharacterRace;
    Definitions::Alignment Alignment;
    QList<int> CurrentStats;

    CharacterModel(QString name, Race Race, Definitions::Alignment align, QList<int> current)
    {
        Name = name;
        CharacterRace = Race;
        Alignment = align;
        CurrentStats = current;
    }
};

#endif // CHARACTER_MODEL_H
