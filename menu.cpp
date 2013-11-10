#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    _pbPlayerVsPlayer(new QPushButton("Player Vs Player", this)),
    _pbPlayerVsIA(new QPushButton("Player Vs IA", this)),
    _pbSettings(new QPushButton("Settings", this)),
    _layV(new QVBoxLayout(this))
{
    _layV->addWidget(_pbPlayerVsPlayer);
    _layV->addWidget(_pbPlayerVsIA);
    _layV->addWidget(_pbSettings);

    QObject::connect(_pbPlayerVsPlayer, SIGNAL(clicked()), this, SIGNAL(playerVsPlayer()));
    QObject::connect(_pbPlayerVsIA, SIGNAL(clicked()), this, SIGNAL(playerVsIA()));
    QObject::connect(_pbSettings, SIGNAL(clicked()), this, SLOT(_pbSettings_clicked()));

    // Temporary
    _pbPlayerVsIA->setEnabled(false);
    _pbPlayerVsIA->setToolTip("Ia is not currently implemented");
}

Menu::~Menu()
{
}

void Menu::_pbSettings_clicked()
{
}
