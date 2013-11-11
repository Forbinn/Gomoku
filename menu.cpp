#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    _pbPlayerVsPlayer(new QPushButton("Player Vs Player", this)),
    _pbPlayerVsIA(new QPushButton("Player Vs IA", this)),
    _pbSettings(new QPushButton("Settings", this)),
    _pbQuit(new QPushButton("Quit", this)),
    _layV(new QVBoxLayout(this))
{
    _layV->addWidget(_pbPlayerVsPlayer);
    _layV->addWidget(_pbPlayerVsIA);
    _layV->addWidget(_pbSettings);
    _layV->addWidget(_pbQuit);

    QObject::connect(_pbPlayerVsPlayer, SIGNAL(clicked()), this, SIGNAL(playerVsPlayer()));
    QObject::connect(_pbPlayerVsIA, SIGNAL(clicked()), this, SIGNAL(playerVsIA()));
    QObject::connect(_pbSettings, SIGNAL(clicked()), this, SIGNAL(settings()));
    QObject::connect(_pbQuit, SIGNAL(clicked()), this, SIGNAL(quit()));

    _pbPlayerVsPlayer->setMinimumHeight(70);
    _pbPlayerVsIA->setMinimumHeight(70);
    _pbSettings->setMinimumHeight(70);
    _pbQuit->setMinimumHeight(70);

    // Temporary
    _pbPlayerVsIA->setEnabled(false);
    _pbPlayerVsIA->setToolTip("Ia is not currently implemented");
}

Menu::~Menu()
{
}
