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
    _listPairWidget1(),
    _listPairWidget2(),
    _run(false)
{
    setupUi(this);

    gridLayout->addWidget(_gameboard, 1, 0, 1, -1);

    pbNewGame->setVisible(false);

    QObject::connect(_gameboard, SIGNAL(mouseClicked(QPoint)), this, SLOT(_gameboard_mouseClicked()));
    QObject::connect(_gameboard, SIGNAL(mouseMoved(QPoint)), this, SLOT(_gameboard_mouseMoved(QPoint)));
    QObject::connect(_arbiter, SIGNAL(winner(const Player*)), this, SLOT(_arbiter_winner(const Player*)));
    QObject::connect(_arbiter, SIGNAL(playerTakePair(const Player*,int)), this, SLOT(_arbiter_playerTakePair(const Player*,int)));
    QObject::connect(pbMenu, SIGNAL(clicked()), this, SIGNAL(menu()));
    QObject::connect(pbNewGame, SIGNAL(clicked()), this, SLOT(reset()));
}

Game::~Game()
{
    foreach (PairWidget *pair, _listPairWidget1)
        delete pair;
    foreach (PairWidget *pair, _listPairWidget2)
        delete pair;
}

void Game::setPlayer1(Player *p1)
{
    if (_p1)
        QObject::disconnect(_p1, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));

    _p1 = p1;
    _gameboard->setPlayer1(p1);
    labelPlayer1->setText(_p1->name());

    QObject::connect(_p1, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));
}

void Game::setPlayer2(Player *p2)
{
    if (_p2)
        QObject::disconnect(_p2, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));

    _p2 = p2;
    _gameboard->setPlayer2(p2);
    labelPlayer2->setText(_p2->name());

    QObject::connect(_p2, SIGNAL(movePlayed(int,int)), this, SLOT(_player_movePlayed(int,int)));
}

void Game::reset()
{
    _actuPlayer = _p1;

    if (_actuPlayer)
    {
        labelPlayerTurn->setText(_actuPlayer->name() + " is your turn");
        iconPlayer->setPixmap(QPixmap::fromImage(_actuPlayer->image()));
    }
    _run = true;
    _gameboard->reset();

    if (_p1)
        _p1->setPairTaken(0);
    if (_p2)
        _p2->setPairTaken(0);

    foreach (PairWidget *pair, _listPairWidget1)
        delete pair;
    foreach (PairWidget *pair, _listPairWidget2)
        delete pair;
    _listPairWidget1.clear();
    _listPairWidget2.clear();
    pbNewGame->setVisible(false);
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

void Game::_gameboard_mouseClicked()
{
    if (!_actuPlayer || !_run)
        return ;
    if (qobject_cast<AI*>(_actuPlayer))
        return ;

    _player_movePlayed(_gameboard->previewCase().x(), _gameboard->previewCase().y());
}

void Game::_gameboard_mouseMoved(const QPoint &p)
{
    if (!_actuPlayer || !_run)
        return ;
    if (qobject_cast<AI*>(_actuPlayer))
        return ;

    int posX = p.x() / _gameboard->caseWidth();
    int posY = p.y() / _gameboard->caseHeight();

    if (!_arbiter->isValid(posX, posY, _actuPlayer))
        return ;

    _gameboard->setPosOfPreviewCase(posX, posY, _actuPlayer);
    _gameboard->update();
}

void Game::_arbiter_winner(const Player *p)
{
    labelPlayerTurn->setText("Player '" + p->name() + "' is the winner");
    _run = false;
    pbNewGame->setVisible(true);
}

void Game::_arbiter_playerTakePair(const Player *p, int nb)
{
    PairWidget *pairWidget;

    if (p == _p1)
    {
        for (int i = 0; i < nb; ++i)
        {
            pairWidget = new PairWidget(_p2, this);
            _listPairWidget1 << pairWidget;
            layPair1->addWidget(pairWidget);
        }
    }
    else
    {
        for (int i = 0; i < nb; ++i)
        {
            pairWidget = new PairWidget(_p1, this);
            _listPairWidget2 << pairWidget;
            layPair2->addWidget(pairWidget);
        }
    }
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
