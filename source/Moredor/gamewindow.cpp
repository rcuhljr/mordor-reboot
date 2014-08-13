#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "createcharacterwidget.h"
#include <QUiLoader>
#include <QFile>
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
//    QUiLoader loader;
//    QFile file(":/forms/createcharacterwidget.ui");
//    file.open(QFile::ReadOnly);
//    QWidget *createCharacterWidget = loader.load(&file, this);
//    file.close();

//    //setCentralWidget(createCharacterWidget);
//    createCharacterWidget->
//    createCharacterWidget->show();

    QDockWidget *dock = new CreateCharacterWidget(this);

    dock->show();


}
