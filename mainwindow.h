#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QStackedWidget>

#include "menu.h"
#include "game.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QMenu *_fileMenu;
    QAction *_newAction;

    QStackedWidget *_stackedWidget;

    Settings *_settings;
    Menu *_menu;
    Game *_game;

private slots:
    void _menu_playerVsPlayer();
    void _menu_settings();
    void _backToMenu();
};

#endif // MAINWINDOW_H
