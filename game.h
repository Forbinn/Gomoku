#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QList>

#include "ui_game.h"
#include "gameboard.h"
#include "player.h"
#include "arbiter.h"
#include "pairwidget.h"

class Game : public QWidget, private Ui::Game
{
    Q_OBJECT

public:
    Game(const Settings *settings, QWidget *parent = 0);
    virtual ~Game();

    inline const Player* player1() const { return _p1; }
    void setPlayer1(Player *p1);
    inline const Player* player2() const { return _p2; }
    void setPlayer2(Player *p2);

    inline const GameBoard* gameBoard() const { return _gameboard; }
    inline GameBoard* gameBoard() { return _gameboard; }
    inline const Arbiter* arbiter() const { return _arbiter; }

public slots:
    void reset();

private:
    void _setPlayer(Player *newPlayer, Player *&oldPlayer);
    void _switchPlayer();

private:
    GameBoard *_gameboard;
    Arbiter *_arbiter;
    Player *_p1;
    Player *_p2;
    Player *_actuPlayer;
    QList<PairWidget*> _listPairWidget1;
    QList<PairWidget*> _listPairWidget2;
    bool _run;

private slots:
    void _gameboard_mouseClicked();
    void _gameboard_mouseMoved(const QPoint &p);
    void _arbiter_winner(const Player *p);
    void _arbiter_playerTakePair(const Player *p, int nb);
    void _arbiter_doubleThree(int x1, int y1, int dx1, int dy1, int x2, int y2, int dx2, int dy2);
    void _player_movePlayed(int x, int y);
    void _ai_finished(int ms);
    void _removeEnlighten();

signals:
    void menu();
    void arbiterError(const QString &error);
    void newMove();
};

#endif // GAME_H
