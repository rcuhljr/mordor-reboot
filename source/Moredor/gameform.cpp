#include "gameform.h"
#include "ui_gameform.h"
#include "townwidget.h"
#include <QMdiSubWindow>
#include <QSizePolicy>

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);
    BuildTownWindow();
}

void GameForm::BuildTownWindow(){
    townWidget = new TownWidget();
    QMdiSubWindow* townWindow = ui->gameArea->addSubWindow(townWidget);
    townWindow->setWindowTitle("The City");
    townWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    townWindow->setFixedSize(townWidget->width()+15, townWidget->height()+35);

}

GameForm::~GameForm()
{
    delete ui;
}
