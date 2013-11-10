#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>

#include "menu.h"
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QMenu *_fileMenu;
    QAction *_newAction;

    Menu *_menu;
    Game *_game;

private slots:
    void _menu_playerVsPlayer();
};

#endif // MAINWINDOW_H
