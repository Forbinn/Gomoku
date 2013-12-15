#include <QPainter>
#include <QVector>
#include <QLine>
#include <QApplication>

#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QFrame(parent),
    _preview(),
    _p1(NULL),
    _p2(NULL),
    _map()
{
    qApp->installEventFilter(this);
}

GameBoard::~GameBoard()
{
}

void GameBoard::setPosOfPreviewCase(int x, int y, Player *p)
{
    _preview.setX(x);
    _preview.setY(y);
    _preview.setOwner(p);
}

bool GameBoard::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this && e->type() == QEvent::MouseMove)
    {
        QMouseEvent *event = static_cast<QMouseEvent*>(e);
        emit mouseMoved(event->pos());
        return true;
    }

    return qApp->eventFilter(obj, e);
}

void GameBoard::reset()
{
    _map.reset();
}

void GameBoard::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    QVector<QLine> lines;
    int x1, y1, x2, y2;
    int lineSpaceWidth = this->width() / (_map.width() + 1);
    int lineSpaceHeight = this->height() / (_map.height() + 1);

    for (int i = 1; i <= _map.width(); ++i)
    {
        x1 = i * lineSpaceWidth;
        y1 = 0;
        x2 = x1;
        y2 = this->height();
        lines << QLine(x1, y1, x2, y2);
    }
    for (int i = 1; i <= _map.height(); ++i)
    {
        x1 = 0;
        y1 = i * lineSpaceHeight;
        x2 = this->width();
        y2 = y1;
        lines << QLine(x1, y1, x2, y2);
    }

    painter.begin(this);
    painter.drawLines(lines);

    if (_p1)
        foreach (const Case *c, _p1->caseOwn())
        {
            int x = (c->x() + 1) * lineSpaceWidth - _p1->image().width() / 2;
            int y = (c->y() + 1) * lineSpaceHeight - _p1->image().height() / 2;

            painter.drawImage(x, y, _p1->image());
        }
    if (_p2)
        foreach (const Case *c, _p2->caseOwn())
        {
            int x = (c->x() + 1) * lineSpaceWidth - _p2->image().width() / 2;
            int y = (c->y() + 1) * lineSpaceHeight - _p2->image().height() / 2;

            painter.drawImage(x, y, _p2->image());
        }

    painter.end();

    QFrame::paintEvent(e);
}

void GameBoard::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseClicked(e->pos());
    QFrame::mouseReleaseEvent(e);
}
