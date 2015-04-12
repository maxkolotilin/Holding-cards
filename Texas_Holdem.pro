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
    src/DeckOfCards.cpp

HEADERS  += mainwindow.h \
    src/DeckOfCards.h

FORMS    += mainwindow.ui
