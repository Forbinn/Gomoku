#include "framecolor.h"

FrameColor::FrameColor(const QColor &c, QWidget *parent) :
    QFrame(parent),
    _colorDialog(new QColorDialog(c, this)),
    _c(c)
{
    this->setFrameShape(QFrame::Box);
    this->setColor(c);

    _colorDialog->setModal(true);

    QObject::connect(_colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(_colorDialog_colorSelected(QColor)));
    QObject::connect(_colorDialog, SIGNAL(rejected()), this, SLOT(_colorDialog_rejected()));
}

FrameColor::~FrameColor()
{
}

void FrameColor::setColor(const QColor &c)
{
    QString style = "QFrame { background: rgb(%1, %2, %3); }";
    this->setStyleSheet(style.arg(c.red()).arg(c.green()).arg(c.blue()));

    _colorDialog->setCurrentColor(c);
    _c = c;
}

void FrameColor::mouseDoubleClickEvent(QMouseEvent *e)
{
    _colorDialog->show();
    this->setStyleSheet("");

    QFrame::mouseDoubleClickEvent(e);
}

void FrameColor::_colorDialog_colorSelected(QColor c)
{
    this->setColor(c);
}

void FrameColor::_colorDialog_rejected()
{
    this->setColor(_c);
}
