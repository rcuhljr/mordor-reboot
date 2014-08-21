#ifndef CHARACTERCREATIONDIALOG_H
#define CHARACTERCREATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CharacterCreationDialog;
}

class CharacterCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterCreationDialog(QWidget *parent = 0);
    ~CharacterCreationDialog();

private:
    Ui::CharacterCreationDialog *ui;
};

#endif // CHARACTERCREATIONDIALOG_H
