#include "player.h"

Player::Player(const QString &name, const QString &imgPath, QObject *parent) :
    QObject(parent),
    _name(name),
    _cases(),
    _img(imgPath, NULL),
    _pairTaken(0)
{
}

Player::~Player()
{
}

bool Player::addCase(const Case *c)
{
    if (_cases.contains(c))
        return false;

    _cases.push_back(c);
    return true;
}

bool Player::removeCase(const Case *c)
{
    if (!_cases.contains(c))
        return false;

    return _cases.removeOne(c);
}
