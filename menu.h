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
    QVBoxLayout *_layV;

private slots:
    void _pbSettings_clicked();

signals:
    void playerVsPlayer();
    void playerVsIA();
};

#endif // MENU_H
