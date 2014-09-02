#include "charactercreationdialog.h"
#include "ui_charactercreationdialog.h"
#include "creationlogic.h"

CharacterCreationDialog::CharacterCreationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CharacterCreationDialog())
    , logic(new CreationLogic())
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

void CharacterCreationDialog::populateUI(){
    ui->raceComboBox->addItems(logic->availableRaces());
}

void CharacterCreationDialog::HandleRaceSelected(int selectedIndex)
{

    QLayoutItem* item;
    while ( ( item = ui->GuildVLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    foreach(const QString guild, logic->getGuilds(selectedIndex))
    {
        QLabel* guildLabel = new QLabel(ui->verticalLayoutWidget);
        guildLabel->setGeometry(QRect(20, 10, 131, 17));
        //QFont f = guildLabel->font();
        //f.setStrikeOut(true);
        //guildLabel->setFont(f);
        guildLabel->setText(guild);
        ui->GuildVLayout->addWidget(guildLabel);
    }
}
