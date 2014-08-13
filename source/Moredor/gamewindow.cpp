#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "createcharacterwidget.h"
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
    QDockWidget *dock = new CreateCharacterWidget(this);

    dock->show();
}
