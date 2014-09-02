#ifndef CHARACTERCREATIONDIALOG_H
#define CHARACTERCREATIONDIALOG_H

#include "creationlogic.h"
#include "race.h"
#include <QDialog>
#include <QSpinBox>

namespace Ui {
class CharacterCreationDialog;
}

class CreationLogic;

class CharacterCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterCreationDialog(QWidget *parent = 0);
    virtual ~CharacterCreationDialog();

private slots:
    void on_exitButton_clicked();
    void HandleRaceSelected(int selectedIndex);

private:
    Ui::CharacterCreationDialog *ui;
    CreationLogic *logic;
    QList<RACE> races;

    void populateUI();
    void SetSpinBoxRange(int raceIndex, QSpinBox* spinBox, CreationLogic::Stats statIndex);
};

#endif // CHARACTERCREATIONDIALOG_H
