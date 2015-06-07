/*
 * Created by Maxim Kolotilin on 27.05.2015
 * e-mail: maxkolmail@gmail.com
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
#include <QObject>

class Game : public QObject
{
public:
    typedef enum { BEGIN, CONTINUE, END } gameStatus_t;

    Game(CardsOnTable *cards, chips_t min_bet, int interval, QObject *parent = 0);
    virtual ~Game();

    void add_player(Player* pl);
    void start();
    virtual void increase_min_bet();

    chips_t get_min_bet() const
    {
        return min_bet;
    }
    const chips_t *get_pot_ptr()
    {
        return &pot;
    }
    const chips_t *get_bets_ptr()
    {
        return &total_bets_in_round;
    }
    const CardsOnTable::round_t *get_round_ptr()
    {
        return &round;
    }
    Evaluator *get_evaluator_ptr()
    {
        return evaluator;
    }
    void set_human_ptr(Player *player)
    {
        human = player;
    }

    virtual void add_to_bets(chips_t bet)
    {
        total_bets_in_round += bet;
    }
    virtual void add_to_pot(chips_t bets_in_round)
    {
        pot += bets_in_round;
    }
    virtual void reset_bets()
    {
        total_bets_in_round = 0;
    }
    virtual void reset_pot()
    {
        pot = 0;
    }

protected:
    void set_random_dealer();
    void set_next_dealer();
    void next_player(player_it &player);
    void search_for_losers();
    void distribute_pot_to_players();
    void deal_cards();
    void reset_players();

    virtual void start_new_deal();
    virtual void end_deal();
    virtual chips_t start_trading();
    virtual void winners();

    gameStatus_t game_status;
    CardsOnTable::round_t round;

    Player *human;
    player_it dealer;

    int number_of_players;
    int number_of_folded;
    int number_of_played_hands;

    chips_t min_bet;           // current min bet in game
    int increase_interval;     // interval of increasing of min bet
    chips_t pot;
    chips_t total_bets_in_round;
    chips_t current_max_bet;
    chips_t size_of_last_raise;  // warning: == new max bet - current max bet!

    DeckOfCards* deck;
    CardsOnTable* cards_on_table;
    Evaluator* evaluator;

    list<Player*> players;
    vector<vector<Player*>> winlist;

};

#endif // GAME_H
