#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = 0);
    ~GameForm();

private:
    Ui::GameForm *ui;
};

#endif // GAMEFORM_H
