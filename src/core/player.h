/*
 * Created by Maxim Kolotilin on 26.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains players classes
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "src/core/evaluator.h"
#include <QObject>

typedef int chips_t;
typedef vector<const Card*>::iterator card_it;

class Evaluator;
class HandStrength;

class Player: public QObject
{
public:
    typedef enum { NONE, CHECK, FOLD, CALL, BET, RAISE, ALL_IN, BIG_BLIND,
                   SMALL_BLIND, SHOW, } player_action_t;
    typedef enum { SMALL, BIG } blind_t;
    typedef struct {
        bool valid;
        player_action_t action;
        chips_t amount;
    } action_t;

    const action_t RESET_ACTION = { false, NONE, 0 };

    Player(string name, int id, chips_t stack, PocketCards *hand,
           QObject *parent = 0);
    virtual ~Player();

    int get_player_id() const
    {
        return player_id;
    }
    chips_t get_stack() const
    {
        return stack;
    }
    PocketCards* get_hand() const
    {
        return hand;
    }
    HandStrength* get_strength() const
    {
        return strength;
    }
    chips_t get_bets_in_round() const
    {
        return my_bets_in_round;
    }
    void reset_my_bets_in_round()
    {
        my_bets_in_round = 0;
    }
    action_t get_last_action() const
    {
        return last_action;
    }
    const string get_name()
    {
        return name;
    }
    bool is_player_in_game()
    {
        return is_in_game;
    }
    void set_card(const Card* card)
    {
        hand->set_card(card);
    }

    virtual void reset_last_action();
    virtual string action_to_string(action_t act);
    virtual void set_fold();
    virtual void set_all_in();
    virtual void set_call(chips_t max_bet_in_round);
    virtual void set_raise(chips_t max_bet_in_round, chips_t raise_size,
                           chips_t bet);

    virtual action_t action(chips_t max_bet_in_round, chips_t raise_size) = 0;
    virtual void set_winner() = 0;
    virtual void enable() = 0;
    virtual chips_t blind(blind_t type);
    virtual chips_t stake(chips_t max_bet_in_round);
    virtual void reset_player();
    virtual void set_dealer(bool switcher);
    virtual void show_hand()
    {
        hand->show_hand();
    }
    virtual void add_to_stack(chips_t gain)
    {
        stack += gain;
    }

    // next function is required for std::sort()
    static bool greater(const Player *pl_1, const Player *pl_2);
    bool operator < (const Player &pl) const;
    bool operator > (const Player &pl) const;
    bool operator == (const Player &pl) const;

    static void set_min_bet(chips_t bet)
    {
        min_bet = bet;
    }

protected:
    const string name;
    const int player_id;

    PocketCards* hand;
    HandStrength* strength;

    chips_t stack;              // player's bank
    chips_t my_bets_in_round;   // player's bets in current round

    action_t last_action;

    bool is_in_game;
    bool is_dealer;

    static const string actions[];
    static const string blinds[];
    // see strings in player.cpp

    static chips_t min_bet;             // current minimum bet in game

};

class HumanPlayer: public Player
{
public:
    HumanPlayer(string name, int id, chips_t stack, PocketCards *hand,
                QObject *parent = 0);
    ~HumanPlayer();

protected:
};

class ComputerPlayer: public Player
{
public:
    static const int FLUSH_DRO_OUTS = 9;
    static const int STRAIGHT_DRO_OUTS = 8;
    static const int GUTSHOT_OUTS = 4;
    static const int PAIR_OUTS = 2;
    static const int TWO_PAIRS_OUTS = 4;
    static const int THREE_TO_FOUR_OUTS = 1;
    static const int HIGH_CARD_OUTS = 3;

    ComputerPlayer(string name, int id, chips_t stack, const chips_t* pot,
                   const chips_t* total_bets, const CardsOnTable::round_t *round,
                   PocketCards *hand, Evaluator *evaluator, QObject *parent = 0);
    ~ComputerPlayer();

    action_t action(chips_t max_bet_in_round, chips_t raise_size);

protected:
    bool is_flush_dro;
    bool is_straight_dro;
    bool is_gutshot;

    int outs;

    const chips_t* pot;
    const chips_t* total_bets_in_round;
    const CardsOnTable::round_t *round;
    Evaluator *evaluator;

    vector<const Card*> all_cards;
    void copy_to_all_cards(const vector<const Card*> *from)
    {
        all_cards.insert(all_cards.end(), from->begin(), from->end());
    }

    // preflop logic
    bool is_hand_in_top_10();
    bool is_hand_in_top_21();
    bool is_connectors();
    bool is_suited();

    // flop, turn, river logic
    bool check_flush_dro();
    bool check_straight_dro();
    bool check_gutshot();
    bool check_gutshot_helper(card_it begin, card_it end);
    int count_outs();
    void current_combination();
    bool check_pot_odds(chips_t bet);

    //    TODO
    //    add check_position
    //    add check_relative_position
    //    add preflop_raisers
    //    add table_image
    //    add discount_chances
    //    add steal_blinds
    //    add bluff
    //    add check_raise
    //    add free_card
    //    add slowplay
    //    add continuation_bet
    //    add floating
};


#endif // PLAYER_H
