#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"
#include "creationlogic.h"


CreationLogic *logic = new CreationLogic();

CharacterCreationDialog::CharacterCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterCreationDialog)
{
    ui->setupUi(this);
    this->populateUI();
}

CharacterCreationDialog::~CharacterCreationDialog()
{
    delete ui;
}

void CharacterCreationDialog::on_exitButton_clicked()
{
    this->close();
}

void CharacterCreationDialog::populateUI(){
    ui->raceComboBox->addItems(logic->availableRaces());
}
