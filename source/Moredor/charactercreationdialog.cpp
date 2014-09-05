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
    connect(DialogUi->strSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));
    connect(DialogUi->intSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));
    connect(DialogUi->wisSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));
    connect(DialogUi->conSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));
    connect(DialogUi->chaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));
    connect(DialogUi->dexSpinBox, SIGNAL(valueChanged(int)), this, SLOT(HandleStatChanged()));

    SetupUi();
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
    close();
}

void CharacterCreationDialog::SetupUi()
{
    foreach(const RACE race, Races)
    {
        DialogUi->raceComboBox->addItem(race.Name, QVariant::fromValue(race));
    }
}

void CharacterCreationDialog::HandleRaceSelected()
{
    RACE currentRace = DialogUi->raceComboBox->currentData().value<RACE>();

    SetStatRange(currentRace, DialogUi->strSpinBox, DialogUi->strRangeLabel, CreationLogic::STR);
    SetStatRange(currentRace, DialogUi->intSpinBox, DialogUi->intRangeLabel, CreationLogic::INT);
    SetStatRange(currentRace, DialogUi->wisSpinBox, DialogUi->wisRangeLabel, CreationLogic::WIS);
    SetStatRange(currentRace, DialogUi->conSpinBox, DialogUi->conRangeLabel, CreationLogic::CON);
    SetStatRange(currentRace, DialogUi->chaSpinBox, DialogUi->chaRangeLabel, CreationLogic::CHA);
    SetStatRange(currentRace, DialogUi->dexSpinBox, DialogUi->dexRangeLabel, CreationLogic::DEX);

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
}

void CharacterCreationDialog::SetStatRange(RACE current, QSpinBox* spinBox, QLabel* rangeLabel, CreationLogic::Stats statIndex)
{
    int minStat = current.StartingStats[statIndex];
    int maxStat = current.MaxStats[statIndex];
    spinBox->setRange(minStat, maxStat);
    spinBox->setValue(minStat);
    rangeLabel->setText(QString("(%1 - %2)").arg(minStat).arg(maxStat));
}

void CharacterCreationDialog::HandleStatChanged()
{
    RACE currentRace = DialogUi->raceComboBox->currentData().value<RACE>();
    int difference = (DialogUi->strSpinBox->value() - currentRace.StartingStats[CreationLogic::STR])
                   + (DialogUi->intSpinBox->value() - currentRace.StartingStats[CreationLogic::INT])
                   + (DialogUi->wisSpinBox->value() - currentRace.StartingStats[CreationLogic::WIS])
                   + (DialogUi->conSpinBox->value() - currentRace.StartingStats[CreationLogic::CON])
                   + (DialogUi->chaSpinBox->value() - currentRace.StartingStats[CreationLogic::CHA])
                   + (DialogUi->dexSpinBox->value() - currentRace.StartingStats[CreationLogic::DEX]);

    bool negativeRemainder = difference > currentRace.StartingPoints;
    DialogUi->saveCharacter->setDisabled(negativeRemainder);

    QPalette palette = DialogUi->remainingStatPointsLabel->palette();
    palette.setColor(DialogUi->remainingStatPointsLabel->foregroundRole(), negativeRemainder ? Qt::red : Qt::black);
    DialogUi->remainingStatPointsLabel->setPalette(palette);
    DialogUi->remainingStatPointsText->setTextColor(negativeRemainder ? Qt::red : Qt::black);

    // Must be done after the text color is set
    DialogUi->remainingStatPointsText->setText(QString("%1").arg(currentRace.StartingPoints - difference));


    UpdateGuildList();
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
