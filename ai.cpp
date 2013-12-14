#include "ai.h"

AI::AI(const QString &name, const QString &imgPath, const Map &map, const Arbiter *arbiter) :
    Player(name, imgPath),
    _thread(new QThread(this)),
    _arbiter(arbiter),
    _map(map),
    _run(false)
{
}

AI::~AI()
{
    _thread->quit();
    _thread->wait();
}

void AI::start()
{
    this->moveToThread(_thread);
    _thread->start();
    QMetaObject::invokeMethod(this, "run", Qt::QueuedConnection);

    _run = true;
}

void AI::stop()
{
    _thread->terminate();

    _run = false;
}

void AI::run()
{
    int x = 0;
    int y = 0;

    while (!_arbiter->isValid(x, y, this))
    {
        ++x;

        if (x >= _map.width())
        {
            x = 0;
            ++y;
        }
    }

    emit movePlayed(x, y);
    _thread->quit();
}
