#ifndef ARBITER_H
#define ARBITER_H

#include <QObject>

#include "map.h"
#include "settings.h"

#define NB_PAIR_FOR_WINNER  5

class Arbiter : public QObject
{
    Q_OBJECT

public:
    enum eErrorType
    {
        NO_ERROR        = 0,
        ALREADY_TAKEN   = 1,
        OUT_OF_BOUND    = 2,
        DOUBLE_3        = 3
    };

public:
    Arbiter(Map *map, const Settings *settings, QObject *parent = NULL);
    virtual ~Arbiter();

    bool setCase(int x, int y, Player *p);
    bool isValid(int x, int y, const Player *p) const;
    bool isValidFast(int x, int y) const;

    inline eErrorType lastError() const { return _errorType; }
    QString lastErrorString() const;

private:
    int _checkAllPairForRemove(int x, int y, const Player *p);
    bool _checkOnePairForRemove(int x, int y, const Player *p, int dx, int dy);
    bool _checkFive(int x, int y, const Player *p) const;
    bool _checkFiveOneLine(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkLineBreakable(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkCoinBreakable(int x, int y, const Player *p) const;
    bool _checkCoinCanBeTake(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkDouble3(int x, int y, const Player *p) const;
    bool _check3Free(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkDouble3Aux(int x, int y, const Player *p, int dx, int dy) const;

private:
    eErrorType _errorType;
    Map *_map;
    const Settings *_settings;

private:
    static int _setXPos;
    static int _setYPos;

signals:
    void playerTakePair(const Player *p, int nb);
    void winner(const Player *p);
    void doubleThree(int x1, int y1, int dx1, int dy1, int x2, int y2, int dx2, int dy2) const;
};

#endif // ARBITER_H
