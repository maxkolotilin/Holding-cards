#include "q_game.h"
#include <QApplication>

QGame::QGame(QLabel *pot, QLabel *bets,
             CardsOnTable *cards, chips_t min_bet, QObject *parent)
    : Game(cards, min_bet)
{
    connect(this, SIGNAL(update_bets(int)),
            bets, SLOT(setNum(int)));
    connect(this, SIGNAL(update_pot(int)),
            pot, SLOT(setNum(int)));

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
