#include "createcharacterwidget.h"
#include "ui_createcharacterwidget.h"
#include <QDebug>

CreateCharacterWidget::CreateCharacterWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::createCharacterWidget)
{    
    qDebug() << " character widget created";
    ui->setupUi(this);
}

CreateCharacterWidget::~CreateCharacterWidget()
{    
    delete ui;
}

void CreateCharacterWidget::on_pushButton_clicked()
{
    qDebug() << "button pressed";
    if(this->close()){
        qDebug() << "closed character widget";
    }else{
        qDebug() << "failed to closed character widget";
    }
}
