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

    connect(ui->raceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleRaceSelected()));
    connect(ui->alignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->strSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->intSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->wisSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->conSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->chaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(ui->dexSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));

    // TODO: Is this necessary?
    HandleRaceSelected();
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

void CharacterCreationDialog::HandleRaceSelected()
{
    RACE currentRace = ui->raceComboBox->currentData().value<RACE>();

    SetSpinBoxRange(currentRace, ui->strSpinBox, CreationLogic::STR);
    SetSpinBoxRange(currentRace, ui->intSpinBox, CreationLogic::INT);
    SetSpinBoxRange(currentRace, ui->wisSpinBox, CreationLogic::WIS);
    SetSpinBoxRange(currentRace, ui->conSpinBox, CreationLogic::CON);
    SetSpinBoxRange(currentRace, ui->chaSpinBox, CreationLogic::CHA);
    SetSpinBoxRange(currentRace, ui->dexSpinBox, CreationLogic::DEX);

    // TODO: Find a better way to do this
    ui->alignmentComboBox->clear();
    if(currentRace.alignments[CreationLogic::Good])
    {
        ui->alignmentComboBox->addItem("Good", QVariant::fromValue(CreationLogic::Good));
    }
    if(currentRace.alignments[CreationLogic::Neutral])
    {
        ui->alignmentComboBox->addItem("Neutral", QVariant::fromValue(CreationLogic::Neutral));
    }
    if(currentRace.alignments[CreationLogic::Evil])
    {
        ui->alignmentComboBox->addItem("Evil", QVariant::fromValue(CreationLogic::Evil));
    }

    // TODO: Is this necessary?
    UpdateGuildList();
}

void CharacterCreationDialog::SetSpinBoxRange(RACE current, QSpinBox* spinBox, CreationLogic::Stats statIndex)
{
    spinBox->setRange(current.startingStats[statIndex], current.maxStats[statIndex]);
    spinBox->setValue(current.startingStats[statIndex]);
}

void CharacterCreationDialog::UpdateGuildList()
{
    QLayoutItem* item;
    while ( ( item = ui->GuildVLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    foreach(const GUILD guild, ui->raceComboBox->currentData().value<RACE>().guilds)
    {
//        QMessageBox msgBox;
//        msgBox.setText(QString("%1").arg(ui->alignmentComboBox->currentData().value<CreationLogic::Alignments>()));
//        msgBox.exec();

        bool meetAlignment = guild.alignments[ui->alignmentComboBox->currentData().value<CreationLogic::Alignments>()];
        bool meetStats = ui->strSpinBox->value() >= guild.requirements[CreationLogic::STR]
                      && ui->intSpinBox->value() >= guild.requirements[CreationLogic::INT]
                      && ui->wisSpinBox->value() >= guild.requirements[CreationLogic::WIS]
                      && ui->conSpinBox->value() >= guild.requirements[CreationLogic::CON]
                      && ui->chaSpinBox->value() >= guild.requirements[CreationLogic::CHA]
                      && ui->dexSpinBox->value() >= guild.requirements[CreationLogic::DEX];

        QLabel* guildLabel = new QLabel(ui->verticalLayoutWidget);
        guildLabel->setGeometry(QRect(20, 10, 131, 17));
        QFont f = guildLabel->font();
        f.setItalic(!meetAlignment && !meetStats);
        f.setBold(meetAlignment && meetStats);
        guildLabel->setFont(f);
        guildLabel->setText(guild.name);
        ui->GuildVLayout->addWidget(guildLabel);
    }
}
