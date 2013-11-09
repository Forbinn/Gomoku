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

    res += _change_up(x, y, p);
    res += _change_up_right(x, y, p);
    res += _change_right(x, y, p);
    res += _change_down_right(x, y, p);
    res += _change_down(x, y, p);
    res += _change_down_left(x, y, p);
    res += _change_left(x, y, p);
    res += _change_up_left(x, y, p);
    return res;
}

int ChangeColor::_change_up(int x, int y, const Player *p)
{
    --y;

    int saveY = y;

    // Search the color of the player
    while (y >= 0)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid()) // The case is empty
            return 0;
        else if (c == p->color()) // Same color found
        {
            int counter = 0;

            ++y;
            // Replace the color of the piece
            while (y <= saveY)
            {
                _frame->setPoint(x, y, p->color());
                ++y;
                ++counter;
            }
            return counter;
        }

        --y;
    }

    return 0;
}

int ChangeColor::_change_up_right(int x, int y, const Player *p)
{
    ++x;
    --y;

    int saveX = x;
    int saveY = y;

    while (x < 19 && y >= 0)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            --x;
            ++y;
            while (x >= saveX && y <= saveY)
            {
                _frame->setPoint(x, y, p->color());
                --x;
                ++y;
                ++counter;
            }
            return counter;
        }

        ++x;
        --y;
    }
    return 0;
}

int ChangeColor::_change_right(int x, int y, const Player *p)
{
    ++x;

    int saveX = x;

    while (x < 19)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            --x;
            while (x >= saveX)
            {
                _frame->setPoint(x, y, p->color());
                --x;
                ++counter;
            }
            return counter;
        }

        ++x;
    }
    return 0;
}

int ChangeColor::_change_down_right(int x, int y, const Player *p)
{
    ++x;
    ++y;

    int saveX = x;
    int saveY = y;

    while (x < 19 && y < 19)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            --x;
            --y;
            while (x >= saveX && y >= saveY)
            {
                _frame->setPoint(x, y, p->color());
                --x;
                --y;
                ++counter;
            }
            return counter;
        }

        ++x;
        ++y;
    }
    return 0;
}

int ChangeColor::_change_down(int x, int y, const Player *p)
{
    ++y;

    int saveY = y;

    while (y < 19)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            --y;
            while (y >= saveY)
            {
                _frame->setPoint(x, y, p->color());
                --y;
                ++counter;
            }
            return counter;
        }

        ++y;
    }

    return 0;
}

int ChangeColor::_change_down_left(int x, int y, const Player *p)
{
    --x;
    ++y;

    int saveX = x;
    int saveY = y;

    while (x >= 0 && y < 19)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            ++x;
            --y;
            while (x <= saveX && y >= saveY)
            {
                _frame->setPoint(x, y, p->color());
                ++x;
                --y;
                ++counter;
            }
            return counter;
        }

        --x;
        ++y;
    }
    return 0;
}

int ChangeColor::_change_left(int x, int y, const Player *p)
{
    --x;

    int saveX = x;

    while (x >= 0)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            ++x;
            while (x <= saveX)
            {
                _frame->setPoint(x, y, p->color());
                ++x;
                ++counter;
            }
            return counter;
        }

        --x;
    }
    return 0;
}

int ChangeColor::_change_up_left(int x, int y, const Player *p)
{
    --x;
    --y;

    int saveX = x;
    int saveY = y;

    while (x >= 0 && y >= 0)
    {
        QColor c = _frame->getPoint(x, y);

        if (!c.isValid())
            return 0;
        else if (c == p->color())
        {
            int counter = 0;

            ++x;
            ++y;
            while (x <= saveX && y <= saveY)
            {
                _frame->setPoint(x, y, p->color());
                ++x;
                ++y;
                ++counter;
            }
            return counter;
        }

        --x;
        --y;
    }
    return 0;
}
