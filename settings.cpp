#include <QAbstractButton>
#include <QLabel>

#include "settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    _layG(new QGridLayout()),
    _cbGameMode(new QComboBox(this)),
    _layV(new QVBoxLayout(this)),
    _buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, Qt::Horizontal, this)),
    _player1Name("Red"),
    _player2Name("Blue"),
    _lePlayer1Name(new QLineEdit(_player1Name, this)),
    _lePlayer2Name(new QLineEdit(_player2Name, this)),
    _frameColor1(new FrameColor(Qt::red, this)),
    _frameColor2(new FrameColor(Qt::blue, this)),
    _gameType(PENTE)
{
    _cbGameMode->addItem("Pente");
    _cbGameMode->addItem("Gomoku Ninuki");

    _layG->addWidget(new QLabel("Game mode", this), 0, 0);
    _layG->addWidget(_cbGameMode, 0, 1, 1, -1);
    _layG->addItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Fixed), 1, 0, 1, -1);
    _layG->addWidget(new QLabel("Player 1 name", this), 2, 0);
    _layG->addWidget(_lePlayer1Name, 2, 1);
    _layG->addWidget(_frameColor1, 2, 2);
    _layG->addWidget(new QLabel("Player 2 name", this), 3, 0);
    _layG->addWidget(_lePlayer2Name, 3, 1);
    _layG->addWidget(_frameColor2, 3, 2);

    _frameColor1->setMinimumHeight(_lePlayer1Name->height());
    _frameColor2->setMinimumHeight(_lePlayer2Name->height());
    _frameColor1->setMinimumWidth(_frameColor1->minimumHeight());
    _frameColor2->setMinimumWidth(_frameColor2->minimumHeight());

    _layV->addLayout(_layG);
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

        _lePlayer1Name->setText(_player1Name);
        _lePlayer2Name->setText(_player2Name);
    }
    else if (role == QDialogButtonBox::AcceptRole || role == QDialogButtonBox::ApplyRole) // Ok || Apply
    {
        switch (_cbGameMode->currentIndex())
        {
            case 0: _gameType = PENTE; break;
            case 1: _gameType = GOMOKU_NINUKI; break;
            default: return ;
        }

        _player1Name = _lePlayer1Name->text();
        _player2Name = _lePlayer2Name->text();

        if (role == QDialogButtonBox::ApplyRole)
            return ;
    }

    emit backToMenu();
}
