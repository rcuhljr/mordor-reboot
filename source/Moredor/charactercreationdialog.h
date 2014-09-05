#ifndef CHARACTER_CREATION_DIALOG_H
#define CHARACTER_CREATION_DIALOG_H

#include "charactermodel.h"
#include "creationlogic.h"
#include "definitions.h"
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

signals:
    void CharacterSaved(CharacterModel character);

private slots:
    void on_exitButton_clicked();
    void on_saveButton_clicked();
    void HandleRaceSelected();
    int GetRemainingStatPoints();
    void HandleStatChanged();
    void UpdateGuildList();

private:
    void SetupUi();
    void SetStatRange(RACE current, QSpinBox* spinBox, QLabel* rangeLabel, Definitions::Stat statIndex);

    Ui::CharacterCreationDialog* DialogUi;
    CreationLogic* Logic;
    QList<RACE> Races;
};

#endif // CHARACTER_CREATION_DIALOG_H
