#-------------------------------------------------
#
# Project created by QtCreator 2013-12-11T20:26:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gomoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    case.cpp \
    player.cpp \
    map.cpp \
    menu.cpp \
    game.cpp \
    gameboard.cpp \
    settings.cpp \
    arbiter.cpp \
    ai.cpp

HEADERS  += mainwindow.h \
    case.h \
    player.h \
    map.h \
    menu.h \
    game.h \
    gameboard.h \
    settings.h \
    arbiter.h \
    ai.h

FORMS += \
    menu.ui \
    game.ui \
    settings.ui

RESOURCES += \
    ressource.qrc
