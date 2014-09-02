#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    virtual ~GameWindow();

private slots:

    void on_createCharacterButton_clicked();

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
