#ifndef CHARACTERTABS_H
#define CHARACTERTABS_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CharacterTabs;
}

class CharacterTabs : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterTabs(QWidget *parent = 0);
    ~CharacterTabs();

private slots:
    void on_statsPushButton_clicked();

    void on_resistPushButton_clicked();

private:
    Ui::CharacterTabs *ui;
    void ResetTabButtonFonts();
    void SelectTabButton(QPushButton* button);
};

#endif // CHARACTERTABS_H
