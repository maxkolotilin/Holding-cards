/*
 * Created by MaximKa on 12.04.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class that evaluates players' hands
 *
 */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "src/cards_on_table.h"
#include "src/pocket_cards.h"
#include "src/player.h"
#include <list>

using std::list;
class Player;

typedef vector<const Card*>::iterator card_it;
typedef list<Player*>::iterator player_it;

class Hand_strength
{
    friend class Evaluator;         //?

public:
    typedef enum { NONE, HIGH_CARD, PAIR, TWO_PAIRS, TREE_OF_A_KIND, STRAIGHT,
                   FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH,
                   ROYAL_FLUSH } Combinations_t;
    static const int NUMBER_OF_COMBINATIONS = 10;

    Hand_strength();
    ~Hand_strength();
    Combinations_t get_combination() const
    {
        return combination;
    }
    const string get_combination_name(Combinations_t c) const
    {
        return combinations[c];
    }
    void clear_comb_cards()
    {
        comb_cards.clear();
    }
    void clear_kicker()
    {
        kicker.clear();
    }
    void reset()
    {
        clear_comb_cards();
        clear_kicker();
        combination = NONE;
    }

    bool operator < (const Hand_strength &hs) const;
    bool operator > (const Hand_strength &hs) const;
    bool operator == (const Hand_strength &hs) const;

private:
    Combinations_t combination;
    static const string combinations[NUMBER_OF_COMBINATIONS];
    // see strings in Evaluator.cpp
    vector<const Card*> comb_cards;
    vector<const Card*> kicker;
};

class Evaluator
{
public:

    Evaluator(Cards_on_table *cards);
    ~Evaluator();

    void get_strength(Hand_strength *strength);
    void get_strength(Pocket_cards *pocket, Hand_strength *strength);

    void get_win_list(list<Player*> &players,
                      vector<vector<Player*>> &winlist);


private:
    bool isTwoPair(Hand_strength *strength);
    bool isStraight(Hand_strength *strength, const int suit = -1);
    bool isFlush(Hand_strength *strength);
    bool isXOfAKind(const int num, Hand_strength *strength);
    bool isFullHouse(Hand_strength *strength);

    void copyToAllCards(const vector<const Card*> *from)
    {
        //std::copy(from->begin(), from->end(), all_cards.end());
        all_cards.insert(all_cards.end(), from->begin(), from->end());
    }
    Cards_on_table *community_cards;
    vector<const Card*> all_cards;
};

#endif // EVALUATOR_H
