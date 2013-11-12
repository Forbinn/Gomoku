#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QLineEdit>

#include "framecolor.h"

class Settings : public QWidget
{
    Q_OBJECT

public:
    enum GameType
    {
        PENTE,          // Standard game
        GOMOKU_NINUKI   // Additional rules
    };

public:
    Settings(QWidget *parent = 0);
    virtual ~Settings();

    inline GameType gameType() const { return _gameType; }
    inline QString player1Name() const { return _player1Name; }
    inline QString player2Name() const { return _player2Name; }
    inline QColor colorPlayer1() const { return _frameColor1->color(); }
    inline QColor colorPlayer2() const { return _frameColor2->color(); }

private:
    QGridLayout *_layG;
    QComboBox *_cbGameMode;
    QVBoxLayout *_layV;
    QDialogButtonBox *_buttonBox;
    QString _player1Name;
    QString _player2Name;
    QLineEdit *_lePlayer1Name;
    QLineEdit *_lePlayer2Name;
    FrameColor *_frameColor1;
    FrameColor *_frameColor2;

    GameType _gameType;

private slots:
    void _buttonBox_clicked(QAbstractButton *button);

signals:
    void backToMenu();
};

#endif // SETTINGS_H
