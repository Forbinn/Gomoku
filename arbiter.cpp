#include "arbiter.h"

Arbiter::Arbiter(Map *map, const Settings *settings, QObject *parent) :
    QObject(parent),
    _errorType(NO_ERROR),
    _map(map),
    _settings(settings),
    _setXPos(0),
    _setYPos(0)
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

    _setXPos = x;
    _setYPos = y;
    if (_settings->double3())
        if (_checkDouble3(x, y, p))
        {
            _errorType = DOUBLE_3;
            return false;
        }

    c.setOwner(p);

    int pairTaken = _checkAllPairForRemove(x, y, p);
    if (pairTaken > 0)
    {
        p->addPairTaken(pairTaken);
        emit playerTakePair(p, pairTaken);
    }

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

bool Arbiter::isValidFast(int x, int y) const
{
    if (x < 0 || x >= _map->width() || y < 0 || y >= _map->height())
        return false;

    if (_map->get(x, y).isAlreadyTaken())
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
        case DOUBLE_3:
            return "Move impossible: double 3";
        default:
            return "Unknow error";
    }
}

int Arbiter::_checkAllPairForRemove(int x, int y, const Player *p)
{
    int pairTaken = 0;

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_checkOnePairForRemove(x, y, p, i, j))
                    ++pairTaken;

    return pairTaken;
}

bool Arbiter::_checkOnePairForRemove(int x, int y, const Player *p, int dx, int dy)
{
    x += dx;
    y += dy;

    Case &c1 = _map->getSafe(x, y);

    if (c1.isNotAlreadyTaken() || c1.isAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    Case &c2 = _map->getSafe(x, y);

    if (c2.isNotAlreadyTaken() || c2.isAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    if (_map->getSafe(x, y).isNotAlreadyTakenBy(p))
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

    if (_map->getSafe(x, y).isNotAlreadyTaken() || _map->getSafe(x, y).isAlreadyTakenBy(p))
        return false;

    x += 2 * dx;
    y += 2 * dy;

    if (_map->getSafe(x, y).isNotAlreadyTakenBy(p))
        return false;

    x += dx;
    y += dy;

    if (_map->getSafe(x, y).isAlreadyTaken() || !Map::isValid(x, y))
        return false;

    return true;
}

bool Arbiter::_checkDouble3(int x, int y, const Player *p) const
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
                if (_check3Free(x, y, p, i, j))
                {
                    while (_map->getSafe(x, y).isAlreadyTakenBy(p))
                    {
                        x -= i;
                        y -= j;
                    }

                    x += i;
                    y += j;

                    if (_checkDouble3Aux(x, y, p, i, j))
                        return true;
                }

    return false;
}

bool Arbiter::_check3Free(int x, int y, const Player *p, int dx, int dy) const
{
    int saveX = x;
    int saveY = y;
    int nbOwnCase = 0;

    x -= dx;
    y -= dy;

    while (_map->getSafe(x, y).isAlreadyTakenBy(p))
    {
        x -= dx;
        y -= dy;
    }

    if (_map->getSafe(x, y).isAlreadyTaken() || !Map::isValid(x, y))
        return false;

    x += dx;
    y += dy;

    for (int i = 0; i < 4; ++i)
    {
        const Case &c = _map->getSafe(x, y);

        if (c.isNotAlreadyTakenBy(p) && c.isAlreadyTaken())
            return false;
        else if (c.isAlreadyTakenBy(p) || (x == _setXPos && y == _setYPos))
            ++nbOwnCase;

        x += dx;
        y += dy;

        if (nbOwnCase == 3)
            break;
    }

    if (_map->getSafe(x, y).isAlreadyTaken() || !Map::isValid(x, y) || (x == saveX && y == saveY))
        return false;

    return nbOwnCase == 3;
}

bool Arbiter::_checkDouble3Aux(int x, int y, const Player *p, int dx, int dy) const
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = -1; j <= 1; ++j)
            for (int k = -1; k <= 1; ++k)
                if ((j != 0 || k != 0) && (j != dx || k != dy) && (j != -dx || k != -dy))
                    if (_check3Free(x, y, p, j, k))
                        return true;

        x += dx;
        y += dy;
    }

    return false;
}
