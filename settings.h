#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDialogButtonBox>

class Settings : public QWidget
{
    Q_OBJECT

public:
    enum GameType
    {
        PENTE,
        GOMOKU_NINUKI
    };

public:
    Settings(QWidget *parent = 0);
    virtual ~Settings();

    inline GameType gameType() const { return _gameType; }

private:
    QFormLayout *_layF;
    QComboBox *_cbGameMode;
    QVBoxLayout *_layV;
    QDialogButtonBox *_buttonBox;

    GameType _gameType;

private slots:
    void _buttonBox_clicked(QAbstractButton *button);

signals:
    void backToMenu();
};

#endif // SETTINGS_H
