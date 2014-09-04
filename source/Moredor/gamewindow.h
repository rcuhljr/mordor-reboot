#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>

namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = 0);
    virtual ~GameWindow();

private slots:
    void on_createCharacterButton_clicked();

private:
    Ui::GameWindow* GameUi;
};

#endif // GAME_WINDOW_H
