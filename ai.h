#ifndef AI_H
#define AI_H

#include <QThread>

/* INCLUDE TEST */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "map.h"
#include "arbiter.h"

class AI : public Player
{
    Q_OBJECT

public:
    AI(const QString &name, const QString &imgPath, const QString &imgPathEnlighten, Map &map, const Arbiter *arbiter);
    virtual ~AI();

    inline bool isRunning() const { return _run; }

public slots:
    void start();
    void stop();
    void run();

private:
    QThread *_thread;
    const Arbiter *_arbiter;
    Map &_map;
    bool _run;
    int _isAlone;
    int	valeur;
    int sx;
    int sy;
    int born;
    int borne;
    int nb;
    int test;
    void findBestValor(int x, int y, Case *solution);
    void passOver(int x, int y);
    void passUnder(int x, int y, Case *solution);
    void isAlone(int x, int y);
    int isEnnemy(int x, int y);
    int Tactic(int x, int y);
    int findDouble(int x, int y);
    int checkDouble(int x, int y, int dx, int dy);
    int findTriple(int x, int y);
    int checkTriple(int x, int y, int dx, int dy);
    int findQuad(int x, int y);
    int checkQuad(int x, int y, int dx, int dy);
    int findWin(int x, int y);
    int checkWin(int x, int y, int dx, int dy);
    bool isAI(int x, int y);
    bool isOpp(int x, int y);

signals:
    void finished(int ms);
};

#endif // AI_H
