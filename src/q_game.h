/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class inherited from Game
 * Add interaction with GUI
 *
 */

#ifndef QGAME_H
#define QGAME_H

#include <QObject>
#include <QLabel>
#include <QApplication>
#include <src/mainwindow.h>
#include <QEventLoop>
#include "src/core/game.h"

class MainWindow;

class QGame : public Game
{
    Q_OBJECT
public:
    explicit QGame(QLabel *pot, QLabel *bets, CardsOnTable *cards,
                   chips_t min_bet, int interval, MainWindow *main_window,
                   QLabel *help_lb, SoundKeeper *sk, QObject *parent = 0);
    ~QGame();

    virtual void increase_min_bet();
    virtual void add_to_bets(chips_t bet);
    virtual void add_to_pot(chips_t bets_in_round);
    virtual void reset_bets();
    virtual void reset_pot();
    virtual void winners();

private:
    MainWindow *window;

    QLabel *help_label;

    SoundKeeper *sound_keeper;

signals:
    void update_bets(int bets);
    void update_pot(int pot);

public slots:
};

#endif // QGAME_H
