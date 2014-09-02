#ifndef CHARACTERCREATIONDIALOG_H
#define CHARACTERCREATIONDIALOG_H

#include <QDialog>

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
    void populateUI();
};

#endif // CHARACTERCREATIONDIALOG_H
