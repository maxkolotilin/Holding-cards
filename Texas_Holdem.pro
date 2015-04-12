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
    src/DeckOfCards.cpp \
    src/card.cpp \
    src/Test.cpp

HEADERS  += mainwindow.h \
    src/DeckOfCards.h \
    src/card.h \
    src/Test.h \
    src/poker_defs.h

FORMS    += mainwindow.ui

CONFIG += console

QMAKE_CXXFLAGS += -std=c++11
