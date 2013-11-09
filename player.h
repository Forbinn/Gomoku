#ifndef PLAYER_H
#define PLAYER_H

#include <QColor>

class Player
{
public:
    Player(QColor c);
    virtual ~Player();

    inline QColor color() const { return _c; }

    inline int pieceTaken() const { return _pieceTaken; }
    inline void setPieceTaken(int pieceTaken) { _pieceTaken = pieceTaken; }

private:
    QColor _c;
    int _pieceTaken;
};

#endif // PLAYER_H
