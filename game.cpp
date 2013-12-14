#include "ai.h"
#include "game.h"

Game::Game(const Settings *settings, QWidget *parent) :
    QWidget(parent),
    Ui::Game(),
    _gameboard(new GameBoard(this)),
    _arbiter(new Arbiter(&_gameboard->map(), settings, this)),
    _p1(NULL),
    _p2(NULL),
    _actuPlayer(NULL),
    _run(false)
{
    setupUi(this);

    gridLayout->addWidget(_gameboard, 1, 0, 1, -1);

    QObject::connect(_gameboard, SIGNAL(mouseClicked(QPoint)), this, SLOT(_gameboard_mouseClicked(QPoint)));
    QObject::connect(_arbiter, SIGNAL(winner(const Player*)), this, SLOT(_arbiter_winner(const Player*)));
    QObject::connect(pbMenu, SIGNAL(clicked()), this, SIGNAL(menu()));
}

Game::~Game()
{
}

void Game::setPlayer1(Player *p1)
{
    if (_p1)
        QObject::disconnect(_p1, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));

    _p1 = p1;
    _gameboard->setPlayer1(p1);

    QObject::connect(_p1, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));
}

void Game::setPlayer2(Player *p2)
{
    if (_p2)
        QObject::disconnect(_p2, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));

    _p2 = p2;
    _gameboard->setPlayer2(p2);

    QObject::connect(_p2, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));
}

void Game::reset()
{
    _actuPlayer = _p1;

    labelPlayerTurn->setText(_actuPlayer->name() + " is your turn");
    iconPlayer->setPixmap(QPixmap::fromImage(_actuPlayer->image()));
    _run = true;
    _gameboard->reset();
}

void Game::_switchPlayer()
{
    if (!_run)
        return ;

    _actuPlayer = (_actuPlayer == _p1) ? _p2 : _p1;
    labelPlayerTurn->setText(_actuPlayer->name() + " is your turn");
    iconPlayer->setPixmap(QPixmap::fromImage(_actuPlayer->image()));

    AI *ai = qobject_cast<AI*>(_actuPlayer);
    if (!ai)
        return ;

    ai->start();
}

void Game::_gameboard_mouseClicked(const QPoint &p)
{
    if (!_actuPlayer || !_run)
        return ;
    if (qobject_cast<AI*>(_actuPlayer))
        return ;

    int posX = p.x() / _gameboard->caseWidth();
    int posY = p.y() / _gameboard->caseHeight();

    _player_movePlayed(posX, posY);
}

void Game::_arbiter_winner(const Player *p)
{
    labelPlayerTurn->setText("Player " + p->name() + " is the winner");
    _run = false;
}

void Game::_player_movePlayed(int x, int y)
{
    if (!_arbiter->setCase(x, y, _actuPlayer))
    {
        emit arbiterError(_arbiter->lastErrorString());
        return ;
    }

    _gameboard->update();
    _switchPlayer();
    emit newMove();
}
