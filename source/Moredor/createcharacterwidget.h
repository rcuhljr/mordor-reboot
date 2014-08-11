#ifndef CREATECHARACTERWIDGET_H
#define CREATECHARACTERWIDGET_H

#include <QDockWidget>

namespace Ui {
class createCharacterWidget;
}

class createCharacterWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit createCharacterWidget(QWidget *parent = 0);
    ~createCharacterWidget();

private:
    Ui::createCharacterWidget *ui;
};

#endif // CREATECHARACTERWIDGET_H
