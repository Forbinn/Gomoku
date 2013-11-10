#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QPoint>
#include <QColor>

class Frame : public QFrame
{
    Q_OBJECT

public:
    Frame(QWidget *parent = 0);
    virtual ~Frame();

    inline void setPoint(const QPoint &p, const QColor &c) { _color[p.x()][p.y()] = c; }
    inline void setPoint(int x, int y, const QColor &c) { _color[x][y] = c; }

    inline void clearPoint(const QPoint &p) { _color[p.x()][p.y()] = QColor(); }
    inline void clearPoint(int x, int y) { _color[x][y] = QColor(); }

    inline QColor getPoint(int x, int y) const { return _color[x][y]; }
    QColor getSafePoint(int x, int y) const;

    void reset();

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    QColor _color[19][19];

signals:
    void mouseClick(QPoint p);
};

#endif // FRAME_H
