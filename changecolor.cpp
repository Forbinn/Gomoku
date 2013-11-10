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

    res += _change_color(x, y, p, 0, -1);
    res += _change_color(x, y, p, 1, -1);
    res += _change_color(x, y, p, 1, 0);
    res += _change_color(x, y, p, 1, 1);
    res += _change_color(x, y, p, 0, 1);
    res += _change_color(x, y, p, -1, 1);
    res += _change_color(x, y, p, -1, 0);
    res += _change_color(x, y, p, -1, -1);
    return res;
}

int ChangeColor::_change_color(int x, int y, const Player *p, int dx, int dy)
{
    x += dx;
    y += dy;

    int saveX = x;
    int saveY = y;

    if (!_frame->getPoint(x, y).isValid())
        return 0;

    x += dx;
    y += dy;

    // Search the color of the player
    while (x >= 0 && x < 19 && y >= 0 && y < 19)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid()) // The case is empty
            return 0;
        else if (c == p->color()) // Same color found
        {
            int counter = 0;

            // Replace the color of the piece
            do
            {
                if (x != saveX)
                    x -= dx;
                if (y != saveY)
                    y -= dy;
                _frame->setPoint(x, y, p->color());
                ++counter;
            }
            while (x != saveX || y != saveY);

            return counter;
        }

        x += dx;
        y += dy;
    }

    return 0;
}
