#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QObject>

namespace Definitions
{
    enum Alignment {Good = 0, Neutral, Evil};
    enum Stat {STR = 0, INT, WIS, CON, CHA, DEX};
}

Q_DECLARE_METATYPE(Definitions::Alignment)

#endif // DEFINITIONS_H
