#ifndef PAIRWIDGET_H
#define PAIRWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "player.h"

class PairWidget : public QWidget
{
    Q_OBJECT

public:
    PairWidget(const Player *p = 0, QWidget *parent = 0);
    virtual ~PairWidget();

    void setPlayer(const Player *p);
    inline const Player* player() const { return _p; }

private:
    QHBoxLayout *_lay;
    QLabel *_coin1;
    QLabel *_coin2;
    const Player *_p;
};

#endif // PAIRWIDGET_H
