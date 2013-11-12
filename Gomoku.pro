#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T17:10:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gomoku
TEMPLATE = app

DESTDIR = ./
MOC_DIR = .moc/
OBJECTS_DIR = .obj/
RCC_DIR = .rcc/
UI_DIR = .ui/
UI_HEADERS_DIR = .ui/header/
UI_SOURCES_DIR = .ui/src/

SOURCES += main.cpp\
        mainwindow.cpp \
    frame.cpp \
    player.cpp \
    arbiter.cpp \
    changecolor.cpp \
    menu.cpp \
    game.cpp \
    settings.cpp \
    framecolor.cpp

HEADERS  += mainwindow.h \
    frame.h \
    player.h \
    arbiter.h \
    changecolor.h \
    menu.h \
    game.h \
    settings.h \
    framecolor.h

FORMS    +=
