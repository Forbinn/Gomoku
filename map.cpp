#include "map.h"

Map::Map() :
    _map(NB_COLUMN * NB_ROW),
    _invalidCase(NULL)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < _map.size(); ++i)
    {
        _map[i].setX(x);
        _map[i].setY(y);

        ++x;
        if (x >= NB_COLUMN)
        {
            x = 0;
            ++y;
        }
    }

    _invalidCase.setX(-1);
    _invalidCase.setY(-1);
}

Map::~Map()
{
}

const Case& Map::getSafe(int x, int y) const
{
    if (x < 0 || x >= NB_COLUMN || y < 0 || y >= NB_ROW)
        return _invalidCase;

    return _map[_index(x, y)];
}

Case& Map::getSafe(int x, int y)
{
    if (x < 0 || x >= NB_COLUMN || y < 0 || y >= NB_ROW)
        return _invalidCase;

    return _map[_index(x, y)];
}

void Map::reset()
{
    for (int i = 0; i < _map.size(); ++i)
        _map[i].clearOwner();
}
