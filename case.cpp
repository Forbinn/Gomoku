#include "case.h"

Case::Case(Player *p /* = NULL */) :
    _owner(p),
    _x(0),
    _y(0),
    _enlighten(false),
    _valor(0)
{
    if (!p)
        return ;

    p->addCase(this);
}

Case::Case(const Case &other) :
    _owner(NULL),
    _x(0),
    _y(0),
    _enlighten(false)
{
    Q_UNUSED(other);
}

Case::~Case()
{
}

Case& Case::operator=(const Case &other)
{
    Q_UNUSED(other);

    return *this;
}

void Case::setOwner(Player *p)
{
    if (_owner)
        _owner->removeCase(this);

    _owner = p;
    p->addCase(this);
}

void Case::clearOwner()
{
    if (!_owner)
        return ;

    _owner->removeCase(this);
    _owner = NULL;
    _enlighten = false;
}
