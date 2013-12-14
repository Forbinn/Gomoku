#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    Ui::Menu()
{
    setupUi(this);

    QObject::connect(pbPlayerVsPlayer, SIGNAL(clicked()), this, SIGNAL(playerVsPlayer()));
    QObject::connect(pbPlayerVsAI, SIGNAL(clicked()), this, SIGNAL(playerVsAI()));
    QObject::connect(pbSettings, SIGNAL(clicked()), this, SIGNAL(settings()));
    QObject::connect(pbQuit, SIGNAL(clicked()), this, SIGNAL(quit()));
}

Menu::~Menu()
{
}
