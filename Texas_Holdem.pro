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
    src/player.cpp \
    src/game.cpp \
    keepers.cpp \
    q_cards_on_table.cpp \
    q_human_player.cpp \
    q_pocket_cards.cpp \
    q_computer_player.cpp

HEADERS  += mainwindow.h \
    src/card.h \
    src/Test.h \
    src/poker_defs.h \
    src/cards_on_table.h \
    src/pocket_cards.h \
    src/deck_of_cards.h \
    src/evaluator.h \
    src/player.h \
    src/game.h \
    keepers.h \
    q_cards_on_table.h \
    q_human_player.h \
    q_pocket_cards.h \
    q_computer_player.h

FORMS    += mainwindow.ui

CONFIG += console

QMAKE_CXXFLAGS += -std=c++11
