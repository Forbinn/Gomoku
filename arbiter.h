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
        ALREADY_TAKEN   = 1
    };

public:
    Arbiter(Map *map, const Settings *settings, QObject *parent = NULL);
    virtual ~Arbiter();

    bool setCase(int x, int y, Player *p);
    bool isValid(int x, int y, const Player *p) const;

    inline eErrorType lastError() const { return _errorType; }
    QString lastErrorString() const;

private:
    int _checkAllPair(int x, int y, const Player *p);
    bool _checkOnePair(int x, int y, const Player *p, int dx, int dy);
    bool _checkFive(int x, int y, const Player *p) const;
    bool _checkFiveOneLine(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkLineBreakable(int x, int y, const Player *p, int dx, int dy) const;
    bool _checkCoinBreakable(int x, int y, const Player *p) const;
    bool _checkCoinCanBeTake(int x, int y, const Player *p, int dx, int dy) const;

private:
    eErrorType _errorType;
    Map *_map;
    const Settings *_settings;

signals:
    void winner(const Player *p);
};

#endif // ARBITER_H
