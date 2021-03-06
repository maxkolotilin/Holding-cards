/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class that evaluates players' hands
 * and class that stores players' combinations
 *
 */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "src/core/cards_on_table.h"
#include "src/core/pocket_cards.h"
#include "src/core/player.h"
#include <list>

using std::list;

class Player;

typedef vector<const Card*>::iterator card_it;
typedef list<Player*>::iterator player_it;

class HandStrength
{

public:
    typedef enum { NONE, HIGH_CARD, PAIR, TWO_PAIRS, TREE_OF_A_KIND, STRAIGHT,
                   FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH,
                   ROYAL_FLUSH } combinations_t;
    static const int NUMBER_OF_COMBINATIONS = 10;
    static const int COMBINATION_CARDS_SIZE = 5;
    static const int KICKER_CARDS_SIZE = 5;

    HandStrength();
    ~HandStrength();

    void set_combination(combinations_t comb)
    {
        combination = comb;
    }
    combinations_t get_combination() const
    {
        return combination;
    }
    const string get_combination_name(combinations_t comb) const
    {
        return combinations[comb];
    }
    void clear_combination_cards()
    {
        combination_cards.clear();
    }
    void clear_kicker_cards()
    {
        kicker_cards.clear();
    }
    void reset_hand_strength();

    // return pointer to constant vector
    const vector<const Card*> *get_combination_cards() const
    {
        return &combination_cards;
    }
    const vector<const Card*> *get_kicker_cards() const
    {
        return &kicker_cards;
    }

    void add_to_combination_cards(const Card *card)
    {
        combination_cards.push_back(card);
    }
    void add_to_kicker_cards(const Card *card)
    {
        kicker_cards.push_back(card);
    }

    bool operator < (const HandStrength &hs) const;
    bool operator > (const HandStrength &hs) const;
    bool operator == (const HandStrength &hs) const;

private:
    combinations_t combination;
    static const string combinations[];
    // see strings in Evaluator.cpp

    vector<const Card*> combination_cards;
    vector<const Card*> kicker_cards;
};

class Evaluator
{
public:
    static const int FOUR_OF_A_KIND_SIZE = 4;
    static const int THREE_OF_A_KIND_SIZE = 3;
    static const int PAIR_SIZE = 2;
    static const int FLUSH_SIZE = 5;
    static const int STRAIGHT_SIZE = 5;

    Evaluator(const CardsOnTable *cards);
    ~Evaluator();

    void determine_strength(PocketCards *pocket, HandStrength *strength);
    void determine_strength(Player* player);
    // warning: next overloaded version DON'T clear all_cards
    void determine_strength(HandStrength *strength);

    void get_win_list(list<Player*> &players,
                      vector<vector<Player*>> &winlist);

    const CardsOnTable *get_communitu_cards()
    {
        return community_cards;
    }

private:
    bool is_two_pairs(HandStrength *strength);
    bool is_straight(HandStrength *strength, const int suit = -1);
    bool is_flush(HandStrength *strength);
    bool is_X_of_a_kind(const int X, HandStrength *strength);
    bool is_full_house(HandStrength *strength);

    void copy_to_all_cards(const vector<const Card*> *from)
    {
        all_cards.insert(all_cards.end(), from->begin(), from->end());
    }

    const CardsOnTable *community_cards;
    vector<const Card*> all_cards;
};

#endif // EVALUATOR_H
