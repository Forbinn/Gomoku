#include "arbiter.h"

Arbiter::Arbiter(Map *map, const Settings *settings, QObject *parent) :
    QObject(parent),
    _errorType(NO_ERROR),
    _map(map),
    _settings(settings)
{
}

Arbiter::~Arbiter()
{
}

bool Arbiter::setCase(int x, int y, Player *p)
{
    if (x < 0 || x >= _map->width() || y < 0 || y >= _map->height())
    {
        _errorType = OUT_OF_BOUND;
        return false;
    }

    Case &c = _map->get(x, y);

    if (c.isAlreadyTaken())
    {
        _errorType = ALREADY_TAKEN;
        return false;
    }

    c.setOwner(p);
    p->addPairTaken(_checkAllPair(x, y, p));

    if (p->pairTaken() >= NB_PAIR_FOR_WINNER)
        emit winner(p);
    if (_checkFive(x, y, p))
        emit winner(p);

    _errorType = NO_ERROR;
    return true;
}

bool Arbiter::isValid(int x, int y, const Player *p) const
{
    Q_UNUSED(p);
    if (x < 0 || x >= _map->width() || y < 0 || y >= _map->height())
        return false;

    Case &c = _map->get(x, y);

    if (c.isAlreadyTaken())
        return false;

    return true;
}

QString Arbiter::lastErrorString() const
{
    switch (_errorType)
    {
        case NO_ERROR:
            return "No error encountered";
        case ALREADY_TAKEN:
            return "This case is already taken";
        case OUT_OF_BOUND:
            return "Move played out of bound";
        default:
            return "Unknow error";
    }
}

int Arbiter::_checkAllPair(int x, int y, const Player *p)
{
    int pairTaken = 0;

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_checkOnePair(x, y, p, i, j))
                    ++pairTaken;

    return pairTaken;
}

bool Arbiter::_checkOnePair(int x, int y, const Player *p, int dx, int dy)
{
    x += dx;
    y += dy;

    Case &c1 = _map->getSafe(x, y);

    if (!c1.isAlreadyTaken() || c1.isAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    Case &c2 = _map->getSafe(x, y);

    if (!c2.isAlreadyTaken() || c2.isAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    if (!_map->getSafe(x, y).isAlreadyTakenBy(p))
        return false;

    c1.clearOwner();
    c2.clearOwner();

    return true;
}

bool Arbiter::_checkFive(int x, int y, const Player *p) const
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_checkFiveOneLine(x, y, p, i, j))
                {
                    if (_settings->breakable5())
                        return _checkLineBreakable(x, y, p, i, j);
                    return true;
                }

    return false;
}

bool Arbiter::_checkFiveOneLine(int x, int y, const Player *p, int dx, int dy) const
{
    int nbCoinOwn = 0;
    int saveX = x;
    int saveY = y;

    while (_map->getSafe(x, y).isAlreadyTakenBy(p))
    {
        x += dx;
        y += dy;
        ++nbCoinOwn;
    }

    if (nbCoinOwn >= 5)
        return true;

    x = saveX - dx;
    y = saveY - dy;

    while (_map->getSafe(x, y).isAlreadyTakenBy(p))
    {
        x -= dx;
        y -= dy;
        ++nbCoinOwn;
    }

    return nbCoinOwn >= 5;
}

bool Arbiter::_checkLineBreakable(int x, int y, const Player *p, int dx, int dy) const
{
    int pairUnbreakable = 0;

    while (_map->getSafe(x + dx, y + dy).isAlreadyTakenBy(p))
    {
        x += dx;
        y += dy;
    }

    while (_map->getSafe(x, y).isAlreadyTakenBy(p))
    {
        if (_checkCoinBreakable(x, y, p))
            pairUnbreakable = 0;
        else
            ++pairUnbreakable;

        x -= dx;
        y -= dy;
    }

    return pairUnbreakable >= 5;
}

bool Arbiter::_checkCoinBreakable(int x, int y, const Player *p) const
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_checkCoinCanBeTake(x, y, p, i, j))
                    return true;

    return false;
}

bool Arbiter::_checkCoinCanBeTake(int x, int y, const Player *p, int dx, int dy) const
{
    x -= dx;
    y -= dy;

    if (!_map->getSafe(x, y).isAlreadyTaken() || _map->getSafe(x, y).isAlreadyTakenBy(p))
        return false;

    x += 2 * dx;
    y += 2 * dy;

    if (!_map->getSafe(x, y).isAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    if (_map->getSafe(x, y).isAlreadyTaken() || !Map::isValid(x, y))
        return false;

    return true;
}
