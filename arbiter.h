#ifndef ARBITER_H
#define ARBITER_H

#include <QString>

#include "frame.h"
#include "player.h"
#include "settings.h"

class Arbiter
{
public:
    Arbiter(const Frame *frame, const Settings *settings);
    virtual ~Arbiter();

    bool isValid(int x, int y, const Player *p);
    bool hasWin(const Player *p, int x, int y) const;

    inline QString errorString() const { return _errorString; }

private:
    bool _checkThisLine(int x, int y, const Player *p, int dx, int dy) const;
    bool _lineIsBreakable(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkBreakableLine(int x, int y, const Player *p, int dx, int dy) const;

private:
    const Frame *_frame;
    const Settings *_settings;
    QString _errorString;
};

#endif // ARBITER_H
