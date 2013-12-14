#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>

#include "ui_settings.h"

class Settings : public QWidget, private Ui::Settings
{
    Q_OBJECT

public:
    Settings(QWidget *parent = 0);
    virtual ~Settings();

    inline QString namePlayer1() const { return lePlayer1->text(); }
    inline void setNamePlayer1(const QString &name) { lePlayer1->setText(name); }
    inline QString namePlayer2() const { return lePlayer2->text(); }
    inline void setNamePlayer2(const QString &name) { lePlayer2->setText(name); }

    inline bool breakable5() const { return cbBreakable5->isChecked(); }
    inline void setBreakable5(bool breakable) { cbBreakable5->setChecked(breakable); }
    inline bool double3() const { return cbDouble3->isChecked(); }
    inline void setDouble3(bool double3) { cbDouble3->setChecked(double3); }

private slots:
    void buttonBox_clicked(QAbstractButton *button);

private:
    void _load();
    void _save();

private:
    QSettings _settings;

signals:
    void cancel();
    void changed();
};

#endif // SETTINGS_H
