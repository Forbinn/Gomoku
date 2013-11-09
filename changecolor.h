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
    int _change_up(int x, int y, const Player *p);
    int _change_up_right(int x, int y, const Player *p);
    int _change_right(int x, int y, const Player *p);
    int _change_down_right(int x, int y, const Player *p);
    int _change_down(int x, int y, const Player *p);
    int _change_down_left(int x, int y, const Player *p);
    int _change_left(int x, int y, const Player *p);
    int _change_up_left(int x, int y, const Player *p);

private:
    Frame *_frame;
};

#endif // CHANGECOLOR_H
