#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T16:11:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Texas_Holdem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/card.cpp \
    src/Test.cpp \
    src/cards_on_table.cpp \
    src/pocket_cards.cpp \
    src/deck_of_cards.cpp \
    src/evaluator.cpp \
   # src/player.cpp \
    src/game.cpp

HEADERS  += mainwindow.h \
    src/card.h \
    src/Test.h \
    src/poker_defs.h \
    src/cards_on_table.h \
    src/pocket_cards.h \
    src/deck_of_cards.h \
    src/evaluator.h \
    #src/player.h \
    src/game.h

FORMS    += mainwindow.ui

CONFIG += console

QMAKE_CXXFLAGS += -std=c++11
