#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

#include "player.h"
#include "frame.h"

class ChangeColor
{
public:
    ChangeColor(Frame *frame);
    virtual ~ChangeColor();

    int change(int x, int y, const Player *p);

private:
    int _check_color(int x, int y, const Player *p, int dx, int dy);

private:
    Frame *_frame;
};

#endif // CHANGECOLOR_H
