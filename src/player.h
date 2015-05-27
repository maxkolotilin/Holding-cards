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

class Player
{
public:
    typedef enum { NONE, RESET_ACTION,

                   CHECK, FOLD, CALL, BET, RAISE, ALL_IN,

                   SHOW,

                   SITOUT } player_action_t;
    typedef enum { SMALL_BLIND, BIG_BLIND } blind_t;

    typedef unsigned int chips_t;

    typedef struct {
        bool valid;
        PlayerAction action;
        chips_t amount;
    } action_t;

    Player(int id);
    virtual ~Player();
    int getClientId() const { return client_id; }
    void resetLastAction() { last_action = Player::NONE; }

    chips_t get_stack() const { return stack; }
    chips_t bets_in_round() const { return bets_in_round; }
    action_t get_last_action() const { return last_action; }
    action_t get_next_action() const { return next_action; }
    void set_min_bet(chips_t bet) { min_bet = bet; }
    void get_won_bank(chips_t bank) { stack += bank; }

    virtual void action() = 0;

    chips_t blind(blind_t type);
    chips_t stake(action_t action);

    Pocket_cards* hand;

protected:
    const int player_id;
    static chips_t min_bet;

    chips_t stack;  // player's bank
    chips_t bets_in_round;

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
    ComputerPlayer(int id);
    ~ComputerPlayer();
protected:
    bool check_top_10_hands();
    bool check_top_21_hands();
    //    TODO
    //    add check_position
    //    add check_relative_position
    //    add count_outs
    //    add count_bank_odds
    //    add preflop_raisers
    //    add table_image
    //    add connectors
};


#endif // PLAYER_H
