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

    QLabel* guild1 = new QLabel(ui->verticalLayoutWidget);
    guild1->setObjectName(QStringLiteral("label"));
    guild1->setGeometry(QRect(20, 10, 131, 17));
    QFont f = guild1->font();
    f.setStrikeOut(true);
    guild1->setFont(f);
    guild1->setText("guild");
    ui->GuildVLayout->addWidget(guild1);
}
