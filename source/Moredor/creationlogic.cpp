#include "creationlogic.h"
#include <string>
#include <QStringList>

CreationLogic::CreationLogic()
{
}


QStringList CreationLogic::availableRaces(){
    QStringList races;
    races.push_back(QString("human"));
    races.push_back(QString("elf"));
    return races;
}
