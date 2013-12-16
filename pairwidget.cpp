#include "pairwidget.h"

PairWidget::PairWidget(const Player *p, QWidget *parent) :
    QWidget(parent),
    _lay(new QHBoxLayout(this)),
    _coin1(new QLabel(this)),
    _coin2(new QLabel(this)),
    _p(p)
{
    _lay->addWidget(_coin1);
    _lay->addWidget(_coin2);

    if (!_p)
        return ;

    _coin1->setPixmap(QPixmap::fromImage(_p->image()));
    _coin2->setPixmap(*_coin1->pixmap());
}

PairWidget::~PairWidget()
{
}

void PairWidget::setPlayer(const Player *p)
{
    _p = p;

    if (!_p)
        return ;

    _coin1->setPixmap(QPixmap::fromImage(_p->image()));
    _coin2->setPixmap(*_coin1->pixmap());
}
