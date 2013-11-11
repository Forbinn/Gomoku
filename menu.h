#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = 0);
    virtual ~Menu();

private:
    QPushButton *_pbPlayerVsPlayer;
    QPushButton *_pbPlayerVsIA;
    QPushButton *_pbSettings;
    QPushButton *_pbQuit;
    QVBoxLayout *_layV;

signals:
    void playerVsPlayer();
    void playerVsIA();
    void settings();
    void quit();
};

#endif // MENU_H
