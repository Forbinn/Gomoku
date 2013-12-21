#include <QStatusBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _stackedWidget(new QStackedWidget(this)),
    _p1(new Player("Player 1", ":/image/whiteCoin", ":/image/whiteCoinEnlighten", this)),
    _p2(new Player("Player 2", ":/image/blackCoin", ":/image/blackCoinEnlighten", this)),
    _settings(new Settings(this)),
    _menu(new Menu(this)),
    _game(new Game(_settings, this)),
    _ai(new AI("AI", ":/image/blackCoin", ":/image/blackCoinEnlighten", _game->gameBoard()->map(), _game->arbiter()))
{
    this->setCentralWidget(_stackedWidget);

    _stackedWidget->addWidget(_menu);
    _stackedWidget->addWidget(_game);
    _stackedWidget->addWidget(_settings);

    _stackedWidget->setCurrentWidget(_menu);

    QObject::connect(_menu, SIGNAL(quit()), this, SLOT(close()));
    QObject::connect(_menu, SIGNAL(playerVsPlayer()), this, SLOT(_menu_playerVsPlayer()));
    QObject::connect(_menu, SIGNAL(playerVsAI()), this, SLOT(_menu_playerVsAI()));
    QObject::connect(_menu, SIGNAL(settings()), this, SLOT(_menu_settings()));
    QObject::connect(_game, SIGNAL(menu()), this, SLOT(_goToMenu()));
    QObject::connect(_game, SIGNAL(arbiterError(QString)), this->statusBar(), SLOT(showMessage(QString)));
    QObject::connect(_game, SIGNAL(newMove()), this->statusBar(), SLOT(clearMessage()));
    QObject::connect(_settings, SIGNAL(cancel()), this, SLOT(_goToMenu()));
    QObject::connect(_settings, SIGNAL(changed()), this, SLOT(_goToMenu()));
}

MainWindow::~MainWindow()
{
    delete _ai;
}

void MainWindow::_menu_playerVsPlayer()
{
    _p1->setName(_settings->namePlayer1());
    _p2->setName(_settings->namePlayer2());

    _game->setPlayer1(_p1);
    _game->setPlayer2(_p2);

    _game->reset();

    _stackedWidget->setCurrentWidget(_game);
}

void MainWindow::_menu_playerVsAI()
{
    _p1->setName(_settings->namePlayer1());
    _ai->setName("AI");

    _game->setPlayer1(_p1);
    _game->setPlayer2(_ai);

    _game->reset();

    _stackedWidget->setCurrentWidget(_game);
}

void MainWindow::_menu_settings()
{
    _stackedWidget->setCurrentWidget(_settings);
}

void MainWindow::_goToMenu()
{
    if (_ai->isRunning())
        _ai->stop();

    this->statusBar()->clearMessage();
    _stackedWidget->setCurrentWidget(_menu);
}
