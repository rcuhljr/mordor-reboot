#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QFormBuilder>
#include <QFile>

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
    QFormBuilder builder;
    QFile file(":/forms/createCharacterWidget.ui");
    file.open(QFile::ReadOnly);
    QWidget *createCharacterWidget = builder.load(&file, this);
    file.close();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(createCharacterWidget);
    setLayout(layout);
}
