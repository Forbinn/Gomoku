#include <QMenuBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _fileMenu(new QMenu("&File", this)),
    _newAction(NULL),
    _menu(new Menu(this)),
    _game(new Game(this))
{
    _newAction = _fileMenu->addAction("New", _game, SLOT(reset()), QKeySequence::New);
    _fileMenu->addAction("Quit", this, SLOT(close()), QKeySequence::Quit);
    this->menuBar()->addMenu(_fileMenu);

    _game->hide();
    this->setCentralWidget(_menu);

    QObject::connect(_menu, SIGNAL(playerVsPlayer()), this, SLOT(_menu_playerVsPlayer()));

    _newAction->setEnabled(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::_menu_playerVsPlayer()
{
    _menu->hide();
    this->setCentralWidget(_game);
    _game->show();

    _newAction->setEnabled(true);
}
