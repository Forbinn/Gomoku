#include <QAbstractButton>

#include "settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    Ui::Settings(),
    _settings("gomoku.ini", QSettings::IniFormat, this)
{
    setupUi(this);

    lePlayer1->setMaxLength(8);
    lePlayer2->setMaxLength(8);

    _load();
    QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonBox_clicked(QAbstractButton*)));
}

Settings::~Settings()
{
    _save();
}

void Settings::_load()
{
    lePlayer1->setText(_settings.value("name1", "Player 1").toString());
    lePlayer2->setText(_settings.value("name2", "Player 2").toString());
    cbBreakable5->setChecked(_settings.value("breakable5", true).toBool());
    cbDouble3->setChecked(_settings.value("double3", true).toBool());
}

void Settings::_save()
{
    _settings.setValue("name1", lePlayer1->text());
    _settings.setValue("name2", lePlayer2->text());
    _settings.setValue("breakable5", cbBreakable5->isChecked());
    _settings.setValue("double3", cbDouble3->isChecked());
}

void Settings::buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = buttonBox->buttonRole(button);

    if (role == QDialogButtonBox::RejectRole)
    {
        _load();
        emit cancel();
    }
    else
    {
        _save();
        emit changed();
    }
}
