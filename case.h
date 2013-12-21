#ifndef CASE_H
#define CASE_H

#include "player.h"

class Case
{
public:
    Case(Player *p = NULL);
    virtual ~Case();

    inline bool isAlreadyTaken() const { return _owner != NULL; }
    inline bool isNotAlreadyTaken() const { return _owner == NULL; }
    inline bool isAlreadyTakenBy(const Player *p) const { return _owner == p; }
    inline bool isNotAlreadyTakenBy(const Player *p) const { return _owner != p; }

    inline const Player* owner() const { return _owner; }
    inline Player* owner() { return _owner; }

    void setOwner(Player *p);
    void clearOwner();

    inline int x() const { return _x; }
    inline void setX(int x) { _x = x; }
    inline int y() const { return _y; }
    inline void setY(int y) { _y = y; }

    inline bool isEnlighten() const { return _enlighten; }
    inline void setEnlighten(bool enlighten) { _enlighten = enlighten; }

private:
    Case(const Case &other);
    Case& operator=(const Case &other);

private:
    Player *_owner;
    int _x;
    int _y;
    bool _enlighten;
};

#endif // CASE_H
