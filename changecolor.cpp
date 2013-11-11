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

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                res += _checkColor(x, y, p, i, j);

    return res;
}

int ChangeColor::_checkColor(int x, int y, const Player *p, int dx, int dy)
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
