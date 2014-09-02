#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"

CharacterCreationDialog::CharacterCreationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CharacterCreationDialog())
    , logic(new CreationLogic())
    , races(logic->getRaces())
{
    ui->setupUi(this);
    this->populateUI();

    connect(ui->raceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleRaceSelected(int)));

    HandleRaceSelected(0);
}

CharacterCreationDialog::~CharacterCreationDialog()
{
    delete ui;
    ui = NULL;
}

void CharacterCreationDialog::on_exitButton_clicked()
{
    this->close();
}

void CharacterCreationDialog::populateUI()
{
    foreach(const RACE race, races)
    {
        ui->raceComboBox->addItem(race.name);
    }
}

void CharacterCreationDialog::HandleRaceSelected(int raceIndex)
{
    QLayoutItem* item;
    while ( ( item = ui->GuildVLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    foreach(const GUILD guild, races[raceIndex].guilds)
    {
        QLabel* guildLabel = new QLabel(ui->verticalLayoutWidget);
        guildLabel->setGeometry(QRect(20, 10, 131, 17));
        //QFont f = guildLabel->font();
        //f.setStrikeOut(true);
        //guildLabel->setFont(f);
        guildLabel->setText(guild.name);
        ui->GuildVLayout->addWidget(guildLabel);
    }

//    ui->alignmentComboBox->clear();
//    foreach(const bool alignAllowed, races[selectedIndex]->alignments)
//    {
//        ui->raceComboBox->addItem(race->name);
//    }

    SetSpinBoxRange(raceIndex, ui->strSpinBox, CreationLogic::STR);
//    SetSpinBoxRange(raceIndex, ui->intSpinBox, CreationLogic::INT);
//    SetSpinBoxRange(raceIndex, ui->wisSpinBox, CreationLogic::WIS);
//    SetSpinBoxRange(raceIndex, ui->conSpinBox, CreationLogic::CON);
//    SetSpinBoxRange(raceIndex, ui->chaSpinBox, CreationLogic::CHA);
//    SetSpinBoxRange(raceIndex, ui->dexSpinBox, CreationLogic::DEX);
}

void CharacterCreationDialog::SetSpinBoxRange(int raceIndex, QSpinBox* spinBox, CreationLogic::Stats statIndex)
{
    spinBox->setRange(races[raceIndex].startingStats[statIndex], races[raceIndex].maxStats[statIndex]);
    spinBox->setValue(races[raceIndex].startingStats[statIndex]);
}
