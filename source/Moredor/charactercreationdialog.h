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

private slots:
    void on_exitButton_clicked();

private:
    Ui::CharacterCreationDialog *ui;
    void CharacterCreationDialog::populateUI();
};

#endif // CHARACTERCREATIONDIALOG_H
