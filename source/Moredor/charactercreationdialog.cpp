#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"

CharacterCreationDialog::CharacterCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterCreationDialog)
{
    ui->setupUi(this);
}

CharacterCreationDialog::~CharacterCreationDialog()
{
    delete ui;
}
