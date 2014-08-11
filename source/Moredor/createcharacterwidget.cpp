#include "createcharacterwidget.h"
#include "ui_createcharacterwidget.h"

createCharacterWidget::createCharacterWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::createCharacterWidget)
{
    ui->setupUi(this);
}

createCharacterWidget::~createCharacterWidget()
{
    delete ui;
}
