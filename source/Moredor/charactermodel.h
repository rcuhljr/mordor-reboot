#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include "definitions.h"
#include "race.h"
#include <QString>

struct CharacterModel
{
    QString Name;
    RACE Race;
    Definitions::Alignment Alignment;
    QList<int> CurrentStats;

    CharacterModel(QString name, RACE race, Definitions::Alignment align, QList<int> current)
    {
        Name = name;
        Race = race;
        Alignment = align;
        CurrentStats = current;
    }
};

#endif // CHARACTER_MODEL_H
