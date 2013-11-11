#include "arbiter.h"

Arbiter::Arbiter(const Frame *frame, const Settings *settings) :
    _frame(frame),
    _settings(settings),
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

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_checkThisLine(x, y, p, i, j))
                    return true;

    return false;
}

bool Arbiter::_checkThisLine(int x, int y, const Player *p, int dx, int dy) const
{
    int saveX = x;
    int saveY = y;
    int minusDx = x;
    int minusDy = y;
    int total = 1;
    bool check = true;
    bool checkMinus = true;

    for (int i = 0; i < 5; ++i)
    {
        if (check)
        {
            x += dx;
            y += dy;

            if (_frame->getSafePoint(x, y) == p->color())
                ++total;
            else
                check = false;
        }

        if (checkMinus)
        {
            minusDx -= dx;
            minusDy -= dy;

            if (_frame->getSafePoint(minusDx, minusDy) == p->color())
            {
                saveX = minusDx; // Save for check if the line is breakable
                saveY = minusDy; // From the beginning of the line
                ++total;
            }
            else
                checkMinus = false;
        }

        if (!check && !checkMinus)
            return total >= 5;
    }

    if (total < 5)
        return false;

    if (_settings->gameType() == Settings::PENTE)
        return true;
    else
        return !_lineIsBreakable(saveX, saveY, p, dx, dy);
}

bool Arbiter::_lineIsBreakable(int x, int y, const Player *p, int dx, int dy) const
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = -1; j <= 1; ++j)
            for (int k = -1; k <= 1; ++k)
                if (j != 0 || k != 0)
                    if (_checkBreakableLine(x, y, p, j, k))
                        return true;

        x += dx;
        y += dy;
    }

    return false;
}

bool Arbiter::_checkBreakableLine(int x, int y, const Player *p, int dx, int dy) const
{
    x -= dx;
    y -= dy;

    QColor c = _frame->getSafePoint(x, y);
    if (!c.isValid() || c == p->color())
        return false;

    x += dx * 2;
    y += dy * 2;

    c = _frame->getSafePoint(x, y);
    if (c != p->color())
        return false;

    x += dx;
    y += dy;

    c = _frame->getSafePoint(x, y);
    if (c.isValid())
        return false;

    return true;
}
