#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "charactercreationdialog.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_createCharacterButton_clicked()
{
    QWidget *charCreate = new CharacterCreationDialog(this);

    charCreate->show();
}
