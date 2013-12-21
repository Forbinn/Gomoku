#ifndef MAP_H
#define MAP_H

#include <QVarLengthArray>

#include "case.h"

#define NB_ROW      19
#define NB_COLUMN   19

class Map
{
public:
    Map();
    virtual ~Map();

    inline const Case& get(int x, int y) const { return _map[_index(x, y)]; }
    inline Case& get(int x, int y) { return _map[_index(x, y)]; }
    const Case& getSafe(int x, int y) const;
    Case& getSafe(int x, int y);

    inline int width() const { return NB_COLUMN; }
    inline int height() const { return NB_ROW; }

    void reset();

public:
    static inline bool isValid(int x, int y) { return x >= 0 && x < NB_COLUMN && y >= 0 && y < NB_ROW; }

private:
    static inline int _index(int x, int y) { return y * NB_COLUMN + x; }

private:
    QVarLengthArray<Case, NB_COLUMN * NB_ROW> _map;
    Case _invalidCase;
};

#endif // MAP_H
