#ifndef FRAMECOLOR_H
#define FRAMECOLOR_H

#include <QFrame>
#include <QColor>
#include <QColorDialog>

class FrameColor : public QFrame
{
    Q_OBJECT

public:
    FrameColor(const QColor &c, QWidget *parent = 0);
    virtual ~FrameColor();

    void setColor(const QColor &c);
    inline QColor color() const { return _colorDialog->currentColor(); }

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

private:
    QColorDialog *_colorDialog;
    QColor _c;

private slots:
    void _colorDialog_colorSelected(QColor c);
    void _colorDialog_rejected();
};

#endif // FRAMECOLOR_H
