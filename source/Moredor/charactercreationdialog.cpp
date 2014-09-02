#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"


#include <QMessageBox>

CharacterCreationDialog::CharacterCreationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CharacterCreationDialog())
    , logic(new CreationLogic())
    , races(logic->getRaces())
{
    ui->setupUi(this);
    this->populateUI();

    connect(ui->raceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleRaceSelected(int)));
    connect(ui->alignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleAlignmentSelected(int)));

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
        ui->raceComboBox->addItem(race.name, QVariant::fromValue(race));
    }
}

void CharacterCreationDialog::HandleRaceSelected(int raceIndex)
{
    RACE current = races[raceIndex];

    SetSpinBoxRange(current, ui->strSpinBox, CreationLogic::STR);
    SetSpinBoxRange(current, ui->intSpinBox, CreationLogic::INT);
    SetSpinBoxRange(current, ui->wisSpinBox, CreationLogic::WIS);
    SetSpinBoxRange(current, ui->conSpinBox, CreationLogic::CON);
    SetSpinBoxRange(current, ui->chaSpinBox, CreationLogic::CHA);
    SetSpinBoxRange(current, ui->dexSpinBox, CreationLogic::DEX);

    // TODO: Find a better way to do this
    ui->alignmentComboBox->clear();
    if(races[raceIndex].alignments[CreationLogic::Good])
    {
        ui->alignmentComboBox->addItem("Good", QVariant::fromValue(CreationLogic::Good));
    }
    if(races[raceIndex].alignments[CreationLogic::Neutral])
    {
        ui->alignmentComboBox->addItem("Neutral", QVariant::fromValue(CreationLogic::Neutral));
    }
    if(races[raceIndex].alignments[CreationLogic::Evil])
    {
        ui->alignmentComboBox->addItem("Evil", QVariant::fromValue(CreationLogic::Evil));
    }
    HandleAlignmentSelected(0);

//    QMessageBox msgBox;
//    msgBox.setText(QString("%1").arg());
//    msgBox.exec();
}

void CharacterCreationDialog::SetSpinBoxRange(RACE current, QSpinBox* spinBox, CreationLogic::Stats statIndex)
{
    spinBox->setRange(current.startingStats[statIndex], current.maxStats[statIndex]);
    spinBox->setValue(current.startingStats[statIndex]);
}

void CharacterCreationDialog::HandleAlignmentSelected(int /*alignmentIndex*/)
{
    QLayoutItem* item;
    while ( ( item = ui->GuildVLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    foreach(const GUILD guild, ui->raceComboBox->currentData().value<RACE>().guilds)
    {
        QLabel* guildLabel = new QLabel(ui->verticalLayoutWidget);
        guildLabel->setGeometry(QRect(20, 10, 131, 17));
        //QFont f = guildLabel->font();
        //f.setStrikeOut(true);
        //guildLabel->setFont(f);
        guildLabel->setText(guild.name);
        ui->GuildVLayout->addWidget(guildLabel);
    }
}
