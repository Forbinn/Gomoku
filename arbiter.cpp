#include "arbiter.h"

Arbiter::Arbiter(const Frame *frame) :
    _frame(frame),
    _errorString()
{
}

Arbiter::~Arbiter()
{
}

bool Arbiter::isValid(int x, int y, const Player *p)
{
    Q_UNUSED(p);

    if (x < 0 || x > 18 || y < 0 || y > 18)
    {
        _errorString = "Move played outside the map";
        return false;
    }

    if (_frame->getPoint(x, y).isValid())
    {
        _errorString = "This case is already taken";
        return false;
    }

    return true;
}

bool Arbiter::hasWin(const Player *p, int x, int y) const
{
    if (p->pieceTaken() >= 10)
        return true;

    if (_check_this_line(x, y, p, 0, -1))
        return true;
    else if (_check_this_line(x, y, p, 1, -1))
        return true;
    else if (_check_this_line(x, y, p, 1, 0))
        return true;
    else if (_check_this_line(x, y, p, 1, 1))
        return true;
    else if (_check_this_line(x, y, p, 0, 1))
        return true;
    else if (_check_this_line(x, y, p, -1, 1))
        return true;
    else if (_check_this_line(x, y, p, -1, 0))
        return true;
    else if (_check_this_line(x, y, p, -1, -1))
        return true;

    return false;
}

bool Arbiter::_check_this_line(int x, int y, const Player *p, int dx, int dy) const
{
    for (int i = 0; i < 5; ++i)
    {
        if (_frame->getSafePoint(x, y) != p->color())
            return false;

        x += dx;
        y += dy;
    }

    return true;
}
