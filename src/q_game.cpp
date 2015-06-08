/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for q_game.h
 *
 */

#include "q_game.h"

QGame::QGame(QLabel *pot, QLabel *bets, CardsOnTable *cards,
             chips_t min_bet, int interval, MainWindow *main_window,
             QObject *parent)
    : Game(cards, min_bet, interval, parent)
{
    connect(this, SIGNAL(update_bets(int)),
            bets, SLOT(setNum(int)));
    connect(this, SIGNAL(update_pot(int)),
            pot, SLOT(setNum(int)));

    window = main_window;

    emit update_bets(this->total_bets_in_round);
    emit update_pot(this->pot);
    QApplication::processEvents();
}

QGame::~QGame()
{
    disconnect();
}

void QGame::increase_min_bet()
{
    Game::increase_min_bet();
    // play sound
}

void QGame::add_to_bets(chips_t bet)
{
    Game::add_to_bets(bet);

    emit update_bets((int)total_bets_in_round);
    QApplication::processEvents();
}

void QGame::add_to_pot(chips_t bets_in_round)
{
    Game::add_to_pot(bets_in_round);

    emit update_pot((int)pot);
    QApplication::processEvents();
}

void QGame::reset_bets()
{
    Game::reset_bets();

    emit update_bets((int)total_bets_in_round);
    QApplication::processEvents();
}

void QGame::reset_pot()
{
    Game::reset_pot();

    emit update_pot((int)pot);
    QApplication::processEvents();
}

void QGame::winners()
{
    Game::winners();

    QEventLoop loop;
    connect(window, SIGNAL(any_button_pushed()),
            &loop, SLOT(quit()));
    loop.exec();
}
