/*
 * Created by MaximKa on 26.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains players classes
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "src/pocket_cards.h"
#include "src/game.h"
#include "src/cards_on_table.h"
#include "src/evaluator.h"

typedef unsigned int chips_t;

class Player
{
public:
    typedef enum { NONE, RESET_ACTION,

                   CHECK, FOLD, CALL, BET, RAISE, ALL_IN,

                   SHOW,

                   SITOUT } player_action_t;
    typedef enum { SMALL_BLIND, BIG_BLIND } blind_t;

    typedef struct {
        bool valid;
        player_action_t action;
        chips_t amount;
    } action_t;

    Player(int id );
    virtual ~Player();
    int get_player_id() const { return player_id; }
    void reset_last_action() { last_action = {false, Player::NONE, 0}; }

    chips_t get_stack() const { return stack; }
    chips_t bets_in_round() const { return bets; }
    action_t get_last_action() const { return last_action; }
    action_t get_next_action() const { return next_action; }
    //void set_min_bet(chips_t bet) { min_bet = bet; }
    void get_won_bank(chips_t bank) { stack += bank; }

    virtual void action() = 0;

    chips_t blind(blind_t type);
    chips_t bet(action_t action);

protected:
    const int player_id;
    const chips_t* min_bet;
    Pocket_cards* hand;
    Hand_strength* strength;

    chips_t stack;  // player's bank
    chips_t bets;

    action_t next_action, last_action;

    bool sitout;     // is player sitting out?
};

class HumanPlayer: public Player
{
public:
    HumanPlayer(int id);
    ~HumanPlayer();
protected:
};

class ComputerPlayer: public Player
{
public:
    ComputerPlayer(int id, const chips_t* pot);
    ~ComputerPlayer();
protected:
    int outs;
    bool is_flush_dro;
    bool is_straight_dro;
    bool is_gutshot;
    const chips_t* pot;
    vector<const Card*> all_cards;
    void copyToAllCards(const vector<const Card*> *from)
    {
        all_cards.insert(all_cards.end(), from->begin(), from->end());
    }
    bool check_top_10_hands();
    bool check_top_21_hands();
    bool check_connectors();
    bool check_suited();
    int count_outs(Evaluator &evaluator, Cards_on_table &community_cards);
    void current_combination(Evaluator &evaluator);
    bool check_pot_odds(chips_t &bet);

    //    TODO
    //    add check_position
    //    add check_relative_position
    //    add preflop_raisers
    //    add table_image
};


#endif // PLAYER_H
