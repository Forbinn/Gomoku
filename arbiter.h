#ifndef ARBITER_H
#define ARBITER_H

#include <QString>

#include "frame.h"
#include "player.h"

class Arbiter
{
public:
    Arbiter(const Frame *frame);
    virtual ~Arbiter();

    bool isValid(int x, int y, const Player *p);
    bool hasWin(const Player *p) const;

    inline QString errorString() const { return _errorString; }

private:
    const Frame *_frame;
    QString _errorString;
};

#endif // ARBITER_H
