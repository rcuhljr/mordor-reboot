#include "gameform.h"
#include "ui_gameform.h"

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);
}

GameForm::~GameForm()
{
    delete ui;
}
