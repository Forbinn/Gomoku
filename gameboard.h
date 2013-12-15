#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPaintEvent>
#include <QMouseEvent>
#include <QFrame>

#include "player.h"
#include "map.h"

class GameBoard : public QFrame
{
    Q_OBJECT

public:
    GameBoard(QWidget *parent = 0);
    virtual ~GameBoard();

    inline const Player* player1() const { return _p1; }
    inline void setPlayer1(const Player *p1) { _p1 = p1; }
    inline const Player* player2() const { return _p2; }
    inline void setPlayer2(const Player *p2) { _p2 = p2; }

    inline const Map& map() const { return _map; }
    inline Map& map() { return _map; }

    inline int caseWidth() const { return this->width() / _map.width(); }
    inline int caseHeight() const { return this->height() / _map.height(); }

    void setPosOfPreviewCase(int x, int y, Player *p);
    inline const Case& previewCase() const { return _preview; }

    virtual bool eventFilter(QObject *obj, QEvent *e);

public slots:
    void reset();

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    Case _preview;
    const Player *_p1;
    const Player *_p2;
    Map _map;

signals:
    void mouseClicked(const QPoint &p);
    void mouseMoved(const QPoint &p);
};

#endif // GAMEBOARD_H
