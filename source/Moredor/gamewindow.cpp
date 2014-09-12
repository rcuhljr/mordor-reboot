#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "charactercreationdialog.h"
#include "gameform.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , GameUi(new Ui::GameWindow())
{
    GameUi->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete GameUi;
    GameUi = NULL;
}

void GameWindow::on_createCharacterButton_clicked()
{
    QWidget* characterCreation = new CharacterCreationDialog(this);

    characterCreation->show();
}

void GameWindow::on_startGameButton_clicked()
{
    GameUi->mainMenuWidget->hide();
    QWidget* gameForm = new GameForm(this);
    gameForm->show();
}
