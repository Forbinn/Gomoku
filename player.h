#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QColor>

class Player
{
public:
    Player(QString name, QColor c);
    virtual ~Player();

    inline QColor color() const { return _c; }
    inline QString name() const { return _name; }

    inline int pieceTaken() const { return _pieceTaken; }
    inline void setPieceTaken(int pieceTaken) { _pieceTaken = pieceTaken; }

private:
    QString _name;
    QColor _c;
    int _pieceTaken;
};

#endif // PLAYER_H
