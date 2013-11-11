#include <QMenuBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _fileMenu(new QMenu("&File", this)),
    _newAction(NULL),
    _stackedWidget(new QStackedWidget(this)),
    _settings(new Settings(this)),
    _menu(new Menu(this)),
    _game(new Game(_settings, this))
{
    _newAction = _fileMenu->addAction("New", _game, SLOT(reset()), QKeySequence::New);
    _fileMenu->addSeparator();
    _fileMenu->addAction("Quit", this, SLOT(close()), QKeySequence::Quit);
    this->menuBar()->addMenu(_fileMenu);

    this->setCentralWidget(_stackedWidget);
    _stackedWidget->addWidget(_game);
    _stackedWidget->addWidget(_menu);
    _stackedWidget->addWidget(_settings);
    _stackedWidget->setCurrentWidget(_menu);

    QObject::connect(_menu, SIGNAL(playerVsPlayer()), this, SLOT(_menu_playerVsPlayer()));
    QObject::connect(_menu, SIGNAL(settings()), this, SLOT(_menu_settings()));
    QObject::connect(_menu, SIGNAL(quit()), this, SLOT(close()));
    QObject::connect(_game, SIGNAL(backToMenu()), this, SLOT(_backToMenu()));
    QObject::connect(_settings, SIGNAL(backToMenu()), this, SLOT(_backToMenu()));

    _newAction->setEnabled(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::_menu_playerVsPlayer()
{
    _stackedWidget->setCurrentWidget(_game);

    _newAction->setEnabled(true);
}

void MainWindow::_menu_settings()
{
    _stackedWidget->setCurrentWidget(_settings);

    _newAction->setEnabled(false);
}

void MainWindow::_backToMenu()
{
    _stackedWidget->setCurrentWidget(_menu);
    _game->reset();

    _newAction->setEnabled(false);
}
