#include <QAbstractButton>

#include "settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    _layF(new QFormLayout()),
    _cbGameMode(new QComboBox(this)),
    _layV(new QVBoxLayout(this)),
    _buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, Qt::Horizontal, this)),
    _gameType(PENTE)
{
    _cbGameMode->addItem("Pente");
    _cbGameMode->addItem("Gomoku Ninuki");

    _layF->addRow("Game mode", _cbGameMode);

    _layV->addLayout(_layF);
    _layV->addItem(new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));
    _layV->addWidget(_buttonBox);

    QObject::connect(_buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(_buttonBox_clicked(QAbstractButton*)));
}

Settings::~Settings()
{
}

void Settings::_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = _buttonBox->buttonRole(button);
    if (role == QDialogButtonBox::RejectRole) // Cancel
    {
        switch (_gameType)
        {
            case PENTE: _cbGameMode->setCurrentIndex(0); break;
            case GOMOKU_NINUKI: _cbGameMode->setCurrentIndex(1); break;
            default: return ;
        }
    }
    else if (role == QDialogButtonBox::AcceptRole || role == QDialogButtonBox::ApplyRole) // Ok || Apply
    {
        switch (_cbGameMode->currentIndex())
        {
            case 0: _gameType = PENTE; break;
            case 1: _gameType = GOMOKU_NINUKI; break;
            default: return ;
        }

        if (role == QDialogButtonBox::ApplyRole)
            return ;
    }

    emit backToMenu();
}
