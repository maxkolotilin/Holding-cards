/*
 * Created by MaximKa on 27.05.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains game's logic
 */

#ifndef GAME_H
#define GAME_H

#include "src/player.h"

typedef unsigned int chips_t;

class Game
{
public:
    typedef enum { BEGIN, CONTINUE, END } gameStatus_t;

    Game(Cards_on_table *cards, chips_t min_bet);
    ~Game();

    void add_player(Player* pl);
    void search_for_losers();
    void winners();

    void game_logic();
    void deal_cards();
    void reset_players();
    void start_new_deal();
    chips_t start_trading();
    virtual void increase_min_bet();

    chips_t get_min_bet() const { return min_bet; }
    virtual void add_to_bets(chips_t bet) {
        bets += bet;
    }
    virtual void add_to_pot(chips_t bets_in_round)
    {
        pot += bets_in_round;
    }
    virtual void reset_bets()
    {
        bets = 0;
    }
    virtual void reset_pot()
    {
        pot = 0;
    }

private:
    gameStatus_t game_status;
    void set_random_dealer();
    int number_of_players;
    int number_of_folded;
    int current_deal;
    chips_t min_bet;
    chips_t pot;
    chips_t bets;
    chips_t current_max_bet;
    int number_of_played_hands;
    Deck_of_cards* deck;
    list<Player*> players;
    vector<vector<Player*>> winlist;
    Cards_on_table* cards_on_table;
    Evaluator* evaluator;
    Cards_on_table::Round_t round;

    player_it dealer;
};

#endif // GAME_H
