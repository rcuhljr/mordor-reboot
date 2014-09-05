#ifndef CHARACTER_CREATION_DIALOG_H
#define CHARACTER_CREATION_DIALOG_H

#include "creationlogic.h"
#include "race.h"
#include <QDialog>
#include <QLabel>
#include <QSpinBox>

namespace Ui
{
    class CharacterCreationDialog;
}

class CreationLogic;

class CharacterCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterCreationDialog(QWidget* parent = 0);
    virtual ~CharacterCreationDialog();

private slots:
    void on_exitButton_clicked();
    void HandleRaceSelected();
    void HandleStatChanged();
    void UpdateGuildList();

private:
    void SetupUi();
    void SetStatRange(RACE current, QSpinBox* spinBox, QLabel* rangeLabel, CreationLogic::Stats statIndex);

    Ui::CharacterCreationDialog* DialogUi;
    CreationLogic* Logic;
    QList<RACE> Races;
};

#endif // CHARACTER_CREATION_DIALOG_H
