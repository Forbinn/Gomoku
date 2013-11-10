#include "player.h"

Player::Player(QString name, QColor c) :
    _name(name),
    _c(c),
    _pieceTaken(0)
{
}

Player::~Player()
{
}
