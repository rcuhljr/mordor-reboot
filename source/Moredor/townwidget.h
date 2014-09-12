#ifndef TOWNWIDGET_H
#define TOWNWIDGET_H

#include <QWidget>

namespace Ui {
class TownWidget;
}

class TownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TownWidget(QWidget *parent = 0);
    ~TownWidget();

private:
    Ui::TownWidget *ui;
};

#endif // TOWNWIDGET_H
