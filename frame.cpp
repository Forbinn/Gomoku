#include <QLine>
#include <QPainter>

#include "frame.h"

Frame::Frame(QWidget *parent) :
    QFrame(parent),
    _color()
{
    this->setFrameShadow(QFrame::Sunken);
    this->setFrameShape(QFrame::Box);
}

Frame::~Frame()
{
}

QColor Frame::getSafePoint(int x, int y) const
{
    if (x < 0 || x > 18 || y < 0 || y > 18)
        return QColor();

    return getPoint(x, y);
}

void Frame::reset()
{
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            _color[i][j] = QColor();

    this->update();
}

void Frame::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    int width = this->rect().width() / 20;
    int height = this->rect().height() / 20;

    for (int i = 1; i < 20; ++i)
    {
        int x1 = i * width;
        int y1 = 0;
        int x2 = i * width;
        int y2 = this->rect().height();

        p.drawLine(x1, y1, x2, y2);

        x1 = 0;
        y1 = i * height;
        x2 = this->rect().width();
        y2 = i * height;

        p.drawLine(x1, y1, x2, y2);
    }

    const int rx = width / 4;
    const int ry = height / 4;

    for (int i = 0; i < 19; ++i)
    {
        int x = (i + 1) * width - rx / 2;
        for (int j = 0; j < 19; ++j)
        {
            if (!_color[i][j].isValid())
                continue;

            int y = (j + 1) * height - ry / 2;

            QPen pen(_color[i][j], rx);
            p.setPen(pen);
            p.drawEllipse(x, y, rx, ry);
        }
    }

    QFrame::paintEvent(e);
}

void Frame::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseClick(e->pos());

    QFrame::mouseReleaseEvent(e);
}
