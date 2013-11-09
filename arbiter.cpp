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
