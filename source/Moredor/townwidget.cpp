#include "townwidget.h"
#include "ui_townwidget.h"

TownWidget::TownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TownWidget)
{
    ui->setupUi(this);
}

TownWidget::~TownWidget()
{
    delete ui;
}
