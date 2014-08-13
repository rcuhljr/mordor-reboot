#ifndef CREATECHARACTERWIDGET_H
#define CREATECHARACTERWIDGET_H

#include <QDockWidget>

namespace Ui {
class createCharacterWidget;
}

class CreateCharacterWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CreateCharacterWidget(QWidget *parent = 0);
    ~CreateCharacterWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::createCharacterWidget *ui;
};

#endif // CREATECHARACTERWIDGET_H
