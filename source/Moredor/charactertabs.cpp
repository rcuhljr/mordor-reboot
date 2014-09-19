#include "charactertabs.h"
#include "ui_charactertabs.h"

CharacterTabs::CharacterTabs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterTabs)
{
    ui->setupUi(this);
}

CharacterTabs::~CharacterTabs()
{
    delete ui;
}

void CharacterTabs::ResetTabButtonFonts(){
    QFont base = ui->statsPushButton->font();
    base.setBold(false);
    ui->statsPushButton->setFont(base);
    ui->resistPushButton->setFont(base);
}

void CharacterTabs::SelectTabButton(QPushButton *button){
    QFont base = button->font();
    base.setBold(true);
    button->setFont(base);
}

void CharacterTabs::on_statsPushButton_clicked()
{
    ResetTabButtonFonts();
    SelectTabButton(ui->statsPushButton);
    ui->stackedWidget->setCurrentIndex(0);
}

void CharacterTabs::on_resistPushButton_clicked()
{
    ResetTabButtonFonts();
    SelectTabButton(ui->resistPushButton);
    ui->stackedWidget->setCurrentIndex(1);
}
