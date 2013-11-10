#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _frame(new Frame(this)),
    _arbiter(new Arbiter(_frame)),
    _player1(new Player("Red", Qt::red)),
    _player2(new Player("Blue", Qt::blue)),
    _changeColor(new ChangeColor(_frame)),
    _player_turn(false),
    _run(true)
{
    _ui->setupUi(this);

    this->centralWidget()->setLayout(_ui->layout);
    _ui->layout->addWidget(_frame, 1);
    _ui->labelPlayerTurn->setText((_player_turn ? _player1->name() : _player2->name()) + " your turn");

    QObject::connect(_frame, SIGNAL(mouseClick(QPoint)), this, SLOT(_frame_mouseClick(QPoint)));
    QObject::connect(_ui->actionNew_game, SIGNAL(triggered()), this, SLOT(_action_New_game_triggered()));
}

MainWindow::~MainWindow()
{
    delete _arbiter;
    delete _player1;
    delete _player2;
    delete _ui;
}

void MainWindow::_frame_mouseClick(QPoint p)
{
    if (!_run)
        return ;

    this->statusBar()->clearMessage();

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

    Player *player = _player_turn ? _player1 : _player2;

    if (!_arbiter->isValid(x, y, player))
    {
        this->statusBar()->showMessage("You canno't play this one: " + _arbiter->errorString());
        return ;
    }

    _frame->setPoint(x, y, player->color());
    int res = _changeColor->change(x, y, player);
    player->setPieceTaken(player->pieceTaken() + res);
    _frame->update();

    if (_arbiter->hasWin(player, x, y))
    {
        _run = false;
        _ui->labelPlayerTurn->setText("Player " + player->name() + " is the winner");
        return ;
    }

    _player_turn = !_player_turn;
    _ui->labelPlayerTurn->setText((_player_turn ? _player1->name() : _player2->name()) + " your turn");

    this->statusBar()->showMessage(_player1->name() + ": " + QString::number(_player1->pieceTaken()) + "\t" + _player2->name() + ": " + QString::number(_player2->pieceTaken()));
}

void MainWindow::_action_New_game_triggered()
{
    _frame->reset();
    _player1->setPieceTaken(0);
    _player2->setPieceTaken(0);
    _run = true;
    _player_turn = false;

    this->statusBar()->clearMessage();
    _ui->labelPlayerTurn->setText((_player_turn ? _player1->name() : _player2->name()) + " your turn");
}
