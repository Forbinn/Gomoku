#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "arbiter.h"
#include "player.h"
#include "frame.h"
#include "changecolor.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(const Settings *settings, QWidget *parent = 0);
    virtual ~Game();

public slots:
    void reset();

private:
    QLabel *_labelPlayerTurn;
    QPushButton *_pbBackMenu;
    QVBoxLayout *_layV;
    QHBoxLayout *_layHInfo;
    QLabel *_labelPieceTaken;
    QLabel *_labelIllegalOperation;

    Frame *_frame;
    Arbiter *_arbiter;
    ChangeColor *_changeColor;
    Player *_player1;
    Player *_player2;
    const Settings *_settings;

    bool _run;
    bool _playerTurn;

private slots:
    void _frame_mouseClick(QPoint p);

signals:
    void backToMenu();
};

#endif // GAME_H
