#ifndef AI_H
#define AI_H

#include <QThread>

#include "player.h"
#include "map.h"
#include "arbiter.h"

class AI : public Player
{
    Q_OBJECT

public:
    AI(const QString &name, const QString &imgPath, const Map &map, const Arbiter *arbiter);
    virtual ~AI();

    inline bool isRunning() const { return _run; }

public slots:
    void start();
    void stop();
    void run();

private:
    QThread *_thread;
    const Arbiter *_arbiter;
    const Map &_map;
    bool _run;

signals:
    void finished(int ms);
};

#endif // AI_H
