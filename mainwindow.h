#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "menu.h"
#include "game.h"
#include "player.h"
#include "settings.h"
#include "ai.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void _menu_playerVsPlayer();
    void _menu_playerVsAI();
    void _menu_settings();
    void _goToMenu();

private:
    QStackedWidget *_stackedWidget;
    Player *_p1;
    Player *_p2;
    Settings *_settings;
    Menu *_menu;
    Game *_game;
    AI *_ai;
};

#endif // MAINWINDOW_H
