#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QDesktopWidget *desktop = qApp->desktop();
    w.resize(640, 480);
    w.move(desktop->width() / 2 - w.width() / 2, desktop->height() / 2 - w.height() / 2);

    return a.exec();
}
