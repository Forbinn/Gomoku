#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ressource);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    w.setFixedSize(1000, 600);
    w.move(a.desktop()->width() / 2 - w.width() / 2, a.desktop()->height() / 2 - w.height() / 2);

    return a.exec();
}
