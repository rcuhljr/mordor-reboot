#ifndef TOWNFRAME_H
#define TOWNFRAME_H

#include <QFrame>

namespace Ui {
class TownFrame;
}

class TownFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TownFrame(QWidget *parent = 0);
    ~TownFrame();

private:
    Ui::TownFrame *ui;
};

#endif // TOWNFRAME_H
