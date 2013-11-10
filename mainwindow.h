#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "frame.h"
#include "player.h"
#include "arbiter.h"
#include "changecolor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    Ui::MainWindow *_ui;
    Frame *_frame;
    Arbiter *_arbiter;
    Player *_player1;
    Player *_player2;
    ChangeColor *_changeColor;
    bool _player_turn;
    bool _run;

private slots:
    void _frame_mouseClick(QPoint p);
    void _action_New_game_triggered();
};

#endif // MAINWINDOW_H
