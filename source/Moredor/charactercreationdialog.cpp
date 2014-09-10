#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"
#include <QMessageBox>

CharacterCreationDialog::CharacterCreationDialog(QWidget* parent)
    : QDialog(parent)
    , DialogUi(new Ui::CharacterCreationDialog())
    , Data(new GameData())
    , Races(Data->GetRaces())
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
    delete Data;
    Data = NULL;

    delete DialogUi;
    DialogUi = NULL;
}

void CharacterCreationDialog::on_exitButton_clicked()
{
    close();
}

void CharacterCreationDialog::on_saveButton_clicked()
{
    int remainingStatPoints = GetRemainingStatPoints();
    if(remainingStatPoints > 0)
    {
        QMessageBox::StandardButton reply =
            QMessageBox::question(this,
                "Unallocated stat points",
                QString("You have %1 stat points remaining.\nNot spending them will make the game harder.\nAre you sure you wish to continue?").arg(remainingStatPoints),
                QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
        {
            return;
        }
    }

    QList<int> currentStats = QList<int>() << DialogUi->strSpinBox->value()
                                           << DialogUi->intSpinBox->value()
                                           << DialogUi->wisSpinBox->value()
                                           << DialogUi->conSpinBox->value()
                                           << DialogUi->chaSpinBox->value()
                                           << DialogUi->dexSpinBox->value();
    emit CharacterSaved(CharacterModel(
                            DialogUi->characterNameBox->toPlainText(),
                            DialogUi->raceComboBox->currentData().value<Race>(),
                            DialogUi->alignmentComboBox->currentData().value<Definitions::Alignment>(),
                            currentStats));
    close();
}

void CharacterCreationDialog::SetupUi()
{
    foreach(const Race Race, Races)
    {
        DialogUi->raceComboBox->addItem(Race.Name, QVariant::fromValue(Race));
    }
}

void CharacterCreationDialog::HandleRaceSelected()
{
    Race currentRace = DialogUi->raceComboBox->currentData().value<Race>();

    SetStatRange(currentRace, DialogUi->strSpinBox, DialogUi->strRangeLabel, Definitions::STR);
    SetStatRange(currentRace, DialogUi->intSpinBox, DialogUi->intRangeLabel, Definitions::INT);
    SetStatRange(currentRace, DialogUi->wisSpinBox, DialogUi->wisRangeLabel, Definitions::WIS);
    SetStatRange(currentRace, DialogUi->conSpinBox, DialogUi->conRangeLabel, Definitions::CON);
    SetStatRange(currentRace, DialogUi->chaSpinBox, DialogUi->chaRangeLabel, Definitions::CHA);
    SetStatRange(currentRace, DialogUi->dexSpinBox, DialogUi->dexRangeLabel, Definitions::DEX);
    HandleStatChanged();

    DialogUi->alignmentComboBox->clear();
    if(currentRace.Alignments[Definitions::Good])
    {
        DialogUi->alignmentComboBox->addItem("Good", QVariant::fromValue(Definitions::Good));
    }
    if(currentRace.Alignments[Definitions::Neutral])
    {
        DialogUi->alignmentComboBox->addItem("Neutral", QVariant::fromValue(Definitions::Neutral));
    }
    if(currentRace.Alignments[Definitions::Evil])
    {
        DialogUi->alignmentComboBox->addItem("Evil", QVariant::fromValue(Definitions::Evil));
    }
}

void CharacterCreationDialog::SetStatRange(Race current, QSpinBox* spinBox, QLabel* rangeLabel, Definitions::Stat stat)
{
    int minStat = current.MinStats[stat];
    int maxStat = current.MaxStats[stat];
    spinBox->setRange(minStat, maxStat);
    spinBox->setValue(minStat);
    rangeLabel->setText(QString("(%1 - %2)").arg(minStat).arg(maxStat));
}

int CharacterCreationDialog::GetRemainingStatPoints()
{
    Race currentRace = DialogUi->raceComboBox->currentData().value<Race>();
    int spentPoints = (DialogUi->strSpinBox->value() - currentRace.MinStats[Definitions::STR])
                    + (DialogUi->intSpinBox->value() - currentRace.MinStats[Definitions::INT])
                    + (DialogUi->wisSpinBox->value() - currentRace.MinStats[Definitions::WIS])
                    + (DialogUi->conSpinBox->value() - currentRace.MinStats[Definitions::CON])
                    + (DialogUi->chaSpinBox->value() - currentRace.MinStats[Definitions::CHA])
                    + (DialogUi->dexSpinBox->value() - currentRace.MinStats[Definitions::DEX]);
    return currentRace.BonusPoints - spentPoints;
}

void CharacterCreationDialog::HandleStatChanged()
{
    int remainingStatPoints = GetRemainingStatPoints();
    bool negativeRemainder = remainingStatPoints < 0;
    DialogUi->saveButton->setDisabled(negativeRemainder);

    QPalette palette = DialogUi->remainingStatPointsLabel->palette();
    palette.setColor(DialogUi->remainingStatPointsLabel->foregroundRole(), negativeRemainder ? Qt::red : Qt::black);
    DialogUi->remainingStatPointsLabel->setPalette(palette);
    DialogUi->remainingStatPointsText->setTextColor(negativeRemainder ? Qt::red : Qt::black);

    // Must be done after the text color is set
    DialogUi->remainingStatPointsText->setText(QString("%1").arg(remainingStatPoints));

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

    foreach(const Guild guild, DialogUi->raceComboBox->currentData().value<Race>().Guilds)
    {
        bool meetAlignment = guild.Alignments[DialogUi->alignmentComboBox->currentData().value<Definitions::Alignment>()];
        bool meetStats = DialogUi->strSpinBox->value() >= guild.RequiredStats[Definitions::STR]
                      && DialogUi->intSpinBox->value() >= guild.RequiredStats[Definitions::INT]
                      && DialogUi->wisSpinBox->value() >= guild.RequiredStats[Definitions::WIS]
                      && DialogUi->conSpinBox->value() >= guild.RequiredStats[Definitions::CON]
                      && DialogUi->chaSpinBox->value() >= guild.RequiredStats[Definitions::CHA]
                      && DialogUi->dexSpinBox->value() >= guild.RequiredStats[Definitions::DEX];

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
