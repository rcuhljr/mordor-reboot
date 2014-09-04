#ifndef CHARACTER_CREATION_DIALOG_H
#define CHARACTER_CREATION_DIALOG_H

#include "creationlogic.h"
#include "race.h"
#include <QDialog>
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
    void UpdateGuildList();

private:
    void PopulateUi();
    void SetSpinBoxRange(RACE current, QSpinBox* spinBox, CreationLogic::Stats statIndex);

    Ui::CharacterCreationDialog* DialogUi;
    CreationLogic* Logic;
    QList<RACE> Races;
};

#endif // CHARACTER_CREATION_DIALOG_H
