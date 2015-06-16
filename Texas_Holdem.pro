#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T16:11:50
#
# Author: Maxim Kolotilin
# e-mail: maxkolmail@gmail.com
#
# Distributed under the Boost Software License, Version 1.0,
# and GNU Lesser General Public License (LGPL) version 3
# http://www.boost.org/LICENSE_1_0.txt
# http://doc.qt.io/qt-5/lgpl.html
#
# It's a part of Texas Hold'em project
#
#-------------------------------------------------

QT       += core gui\
            multimedia\
            declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Texas_Holdem
TEMPLATE = app


SOURCES += main.cpp\
        src/mainwindow.cpp \
    src/core/card.cpp \
    src/core/Test.cpp \
    src/core/cards_on_table.cpp \
    src/core/pocket_cards.cpp \
    src/core/deck_of_cards.cpp \
    src/core/evaluator.cpp \
    src/core/player.cpp \
    src/core/game.cpp \
    src/keepers.cpp \
    src/q_cards_on_table.cpp \
    src/q_human_player.cpp \
    src/q_pocket_cards.cpp \
    src/q_computer_player.cpp \
    src/q_game.cpp

HEADERS  += src/mainwindow.h \
    src/core/card.h \
    src/core/Test.h \
    src/core/poker_defs.h \
    src/core/cards_on_table.h \
    src/core/pocket_cards.h \
    src/core/deck_of_cards.h \
    src/core/evaluator.h \
    src/core/player.h \
    src/core/game.h \
    src/keepers.h \
    src/q_cards_on_table.h \
    src/q_human_player.h \
    src/q_pocket_cards.h \
    src/q_computer_player.h \
    src/q_game.h

FORMS    += mainwindow.ui

#CONFIG += console

QMAKE_CXXFLAGS += -std=c++11

DISTFILES += \
    res/qml/flip.qml
