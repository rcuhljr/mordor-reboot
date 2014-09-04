#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"

CharacterCreationDialog::CharacterCreationDialog(QWidget* parent)
    : QDialog(parent)
    , DialogUi(new Ui::CharacterCreationDialog())
    , Logic(new CreationLogic())
    , Races(Logic->GetRaces())
{
    DialogUi->setupUi(this);

    connect(DialogUi->raceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleRaceSelected()));
    connect(DialogUi->alignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->strSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->intSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->wisSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->conSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->chaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));
    connect(DialogUi->dexSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGuildList()));

    this->PopulateUi();
}

CharacterCreationDialog::~CharacterCreationDialog()
{
    delete Logic;
    Logic = NULL;

    delete DialogUi;
    DialogUi = NULL;
}

void CharacterCreationDialog::on_exitButton_clicked()
{
    this->close();
}

void CharacterCreationDialog::PopulateUi()
{
    foreach(const RACE race, Races)
    {
        DialogUi->raceComboBox->addItem(race.Name, QVariant::fromValue(race));
    }

    // TODO: Is this necessary?
    HandleRaceSelected();
}

void CharacterCreationDialog::HandleRaceSelected()
{
    RACE currentRace = DialogUi->raceComboBox->currentData().value<RACE>();

    SetSpinBoxRange(currentRace, DialogUi->strSpinBox, CreationLogic::STR);
    SetSpinBoxRange(currentRace, DialogUi->intSpinBox, CreationLogic::INT);
    SetSpinBoxRange(currentRace, DialogUi->wisSpinBox, CreationLogic::WIS);
    SetSpinBoxRange(currentRace, DialogUi->conSpinBox, CreationLogic::CON);
    SetSpinBoxRange(currentRace, DialogUi->chaSpinBox, CreationLogic::CHA);
    SetSpinBoxRange(currentRace, DialogUi->dexSpinBox, CreationLogic::DEX);

    // TODO: Find a better way to do this
    DialogUi->alignmentComboBox->clear();
    if(currentRace.Alignments[CreationLogic::Good])
    {
        DialogUi->alignmentComboBox->addItem("Good", QVariant::fromValue(CreationLogic::Good));
    }
    if(currentRace.Alignments[CreationLogic::Neutral])
    {
        DialogUi->alignmentComboBox->addItem("Neutral", QVariant::fromValue(CreationLogic::Neutral));
    }
    if(currentRace.Alignments[CreationLogic::Evil])
    {
        DialogUi->alignmentComboBox->addItem("Evil", QVariant::fromValue(CreationLogic::Evil));
    }

    // TODO: Is this necessary?
    UpdateGuildList();
}

void CharacterCreationDialog::SetSpinBoxRange(RACE current, QSpinBox* spinBox, CreationLogic::Stats statIndex)
{
    spinBox->setRange(current.StartingStats[statIndex], current.MaxStats[statIndex]);
    spinBox->setValue(current.StartingStats[statIndex]);
}

void CharacterCreationDialog::UpdateGuildList()
{
    QLayoutItem* item;
    while ( ( item = DialogUi->GuildVLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    foreach(const GUILD guild, DialogUi->raceComboBox->currentData().value<RACE>().Guilds)
    {
        bool meetAlignment = guild.Alignments[DialogUi->alignmentComboBox->currentData().value<CreationLogic::Alignments>()];
        bool meetStats = DialogUi->strSpinBox->value() >= guild.RequiredStats[CreationLogic::STR]
                      && DialogUi->intSpinBox->value() >= guild.RequiredStats[CreationLogic::INT]
                      && DialogUi->wisSpinBox->value() >= guild.RequiredStats[CreationLogic::WIS]
                      && DialogUi->conSpinBox->value() >= guild.RequiredStats[CreationLogic::CON]
                      && DialogUi->chaSpinBox->value() >= guild.RequiredStats[CreationLogic::CHA]
                      && DialogUi->dexSpinBox->value() >= guild.RequiredStats[CreationLogic::DEX];

        QLabel* guildLabel = new QLabel(DialogUi->verticalLayoutWidget);
        guildLabel->setGeometry(QRect(20, 10, 131, 17));
        QFont f = guildLabel->font();
        f.setItalic(!meetAlignment && !meetStats);
        f.setBold(meetAlignment && meetStats);
        guildLabel->setFont(f);
        guildLabel->setText(guild.Name);
        DialogUi->GuildVLayout->addWidget(guildLabel);
    }
}
