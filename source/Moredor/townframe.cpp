#include "townframe.h"
#include "ui_townframe.h"

TownFrame::TownFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TownFrame)
{
    ui->setupUi(this);
}

TownFrame::~TownFrame()
{
    delete ui;
}
