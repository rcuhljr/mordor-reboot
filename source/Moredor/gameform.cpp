#include "gameform.h"
#include "ui_gameform.h"
#include "townwidget.h"
#include "charactertabs.h"
#include <QMdiSubWindow>

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);
    BuildTownWindow();
    BuildCharacterTabs();
}

void GameForm::BuildTownWindow(){
    townWidget = new TownWidget();
    QMdiSubWindow* townWindow = ui->gameArea->addSubWindow(townWidget);
    townWindow->setWindowTitle("The City");
    townWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    townWindow->setFixedSize(townWidget->width()+15, townWidget->height()+35);

}

void GameForm::BuildCharacterTabs(){
    tabsWidget = new CharacterTabs();
    QMdiSubWindow* tabsWindow = ui->gameArea->addSubWindow(tabsWidget);
    tabsWindow->setWindowTitle("PlayerName");
    tabsWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    tabsWindow->setFixedSize(tabsWidget->width()+15, tabsWidget->height()+35);

}

GameForm::~GameForm()
{
    delete ui;
}
