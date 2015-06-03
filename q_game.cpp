#include "q_game.h"

QGame::QGame(QLabel *pot, QLabel *bets,
             Cards_on_table *cards, chips_t min_bet, QObject *parent)
    : QObject(parent), Game(cards, min_bet)
{
    connect(this, SIGNAL(update_bets(chips_t)),
            bets, SLOT(setNum(int)));
    connect(this, SIGNAL(update_pot(chips_t)),
            pot, SLOT(setNum(int)));
}

QGame::~QGame()
{
    disconnect();
}

void QGame::increase_min_bet()
{
    Game::increase_min_bet();
}

void QGame::add_to_bets(chips_t bet)
{
    Game::add_to_bets(bet);

    emit update_bets(bets);
}

void QGame::add_to_pot(chips_t bets_in_round)
{
    Game::add_to_pot(bets_in_round);

    emit update_pot(pot);
}

void QGame::reset_bets()
{
    Game::reset_bets();

    emit update_bets(bets);
}

void QGame::reset_pot()
{
    Game::reset_pot();

    emit update_pot(pot);
}
