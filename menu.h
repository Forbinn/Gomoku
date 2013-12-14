#ifndef MENU_H
#define MENU_H

#include <QWidget>

#include "ui_menu.h"

class Menu : public QWidget, private Ui::Menu
{
    Q_OBJECT

public:
    Menu(QWidget *parent = 0);
    virtual ~Menu();

signals:
    void playerVsPlayer();
    void playerVsAI();
    void settings();
    void quit();
};

#endif // MENU_H
