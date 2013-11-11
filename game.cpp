#include <QFont>

#include "game.h"

Game::Game(const Settings *settings, QWidget *parent) :
    QWidget(parent),
    _labelPlayerTurn(new QLabel(this)),
    _pbBackMenu(new QPushButton("< Back to menu", this)),
    _frame(new Frame(this)),
    _layV(new QVBoxLayout(this)),
    _arbiter(new Arbiter(_frame, settings)),
    _changeColor(new ChangeColor(_frame)),
    _player1(new Player("Red", Qt::red)),
    _player2(new Player("Blue", Qt::blue)),
    _layHInfo(new QHBoxLayout()),
    _labelPieceTaken(new QLabel(this)),
    _labelIllegalOperation(new QLabel(this)),
    _run(true),
    _playerTurn(true)
{
    _labelPieceTaken->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _labelIllegalOperation->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    _layHInfo->addWidget(_labelPieceTaken);
    _layHInfo->addWidget(_labelIllegalOperation);

    QFont font(_labelPlayerTurn->font());
    font.setPixelSize(20);

    _labelPlayerTurn->setAlignment(Qt::AlignCenter);
    _labelPlayerTurn->setFont(font);
    _layV->addWidget(_labelPlayerTurn);
    _layV->addWidget(_frame, 1);
    _layV->addLayout(_layHInfo);

    QObject::connect(_frame, SIGNAL(mouseClick(QPoint)), this, SLOT(_frame_mouseClick(QPoint)));

    _labelPlayerTurn->setText((_playerTurn ? _player1->name() : _player2->name()) + " your turn");
    _labelPieceTaken->setText(_player1->name() + ": " + QString::number(_player1->pieceTaken()) + " - " + _player2->name() + ": " + QString::number(_player2->pieceTaken()));
    _labelIllegalOperation->clear();

    _pbBackMenu->move(5, 5);

    QObject::connect(_pbBackMenu, SIGNAL(clicked()), this, SIGNAL(backToMenu()));
}

Game::~Game()
{
    delete _arbiter;
    delete _changeColor;
    delete _player1;
    delete _player2;
}

void Game::reset()
{
    _frame->reset();

    _run = true;
    _playerTurn = true;
    _player1->setPieceTaken(0);
    _player2->setPieceTaken(0);

    _labelPlayerTurn->setText((_playerTurn ? _player1->name() : _player2->name()) + " your turn");
    _labelPieceTaken->setText(_player1->name() + ": " + QString::number(_player1->pieceTaken()) + " - " + _player2->name() + ": " + QString::number(_player2->pieceTaken()));
    _labelIllegalOperation->clear();
}

void Game::_frame_mouseClick(QPoint p)
{
    if (!_run)
        return ;

    _labelIllegalOperation->clear();

    float width = _frame->rect().width() / 20.f;
    float height = _frame->rect().height() / 20.f;
    p.setX(p.x() - width);
    p.setY(p.y() - height);
    float xf = float(p.x()) / width;
    float yf = float(p.y()) / height;

    int x = xf;
    int y = yf;
    float resX = xf - x;
    float resY = yf - y;
    if (resX > 0.5f)
        ++x;
    if (resY > 0.5f)
        ++y;

    Player *player = _playerTurn ? _player1 : _player2;

    if (!_arbiter->isValid(x, y, player))
    {
        _labelIllegalOperation->setText("Illegal move: " + _arbiter->errorString());
        return ;
    }

    _frame->setPoint(x, y, player->color());
    int res = _changeColor->change(x, y, player);
    player->setPieceTaken(player->pieceTaken() + res);
    _frame->update();

    if (_arbiter->hasWin(player, x, y))
    {
        _run = false;
        _labelPlayerTurn->setText("Player " + player->name() + " is the winner");
        return ;
    }

    _playerTurn = !_playerTurn;
    _labelPlayerTurn->setText((_playerTurn ? _player1->name() : _player2->name()) + " your turn");
    _labelPieceTaken->setText(_player1->name() + ": " + QString::number(_player1->pieceTaken()) + " - " + _player2->name() + ": " + QString::number(_player2->pieceTaken()));
}

