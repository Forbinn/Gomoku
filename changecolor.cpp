#include "changecolor.h"

ChangeColor::ChangeColor(Frame *frame) :
    _frame(frame)
{
}

ChangeColor::~ChangeColor()
{
}

int ChangeColor::change(int x, int y, const Player *p)
{
    int res = 0;

    res += _check_color(x, y, p, 0, -1);
    res += _check_color(x, y, p, 1, -1);
    res += _check_color(x, y, p, 1, 0);
    res += _check_color(x, y, p, 1, 1);
    res += _check_color(x, y, p, 0, 1);
    res += _check_color(x, y, p, -1, 1);
    res += _check_color(x, y, p, -1, 0);
    res += _check_color(x, y, p, -1, -1);
    return res;
}

int ChangeColor::_check_color(int x, int y, const Player *p, int dx, int dy)
{
    int saveX = x;
    int saveY = y;

    for (int i = 0; i < 2; ++i)
    {
        x += dx;
        y += dy;

        QColor c = _frame->getSafePoint(x, y);
        if (!c.isValid() || c == p->color())
            return 0;
    }

    x += dx;
    y += dy;
    QColor c = _frame->getSafePoint(x, y);
    if (c != p->color())
        return 0;

    x = saveX;
    y = saveY;

    for (int i = 0; i < 2; ++i)
    {
        x += dx;
        y += dy;

        _frame->setPoint(x, y, QColor());
    }

    return 2;
}
