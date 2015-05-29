/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class that evaluates players' hands
 *
 */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "src/deck_of_cards.h"
#include "src/cards_on_table.h"
#include "src/pocket_cards.h"

typedef vector<const Card*>::iterator iterator_t;

class Hand_strength
{
    friend class Evaluator;         //?

public:
    typedef enum { HIGH_CARD, PAIR, TWO_PAIRS, TREE_OF_A_KIND, STRAIGHT,
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

    bool operator < (const Hand_strength &hs) const;
    bool operator > (const Hand_strength &hs) const;
    bool operator == (const Hand_strength &hs) const;

private:
    Combinations_t combination;
    //see strings in Evaluator.cpp
    static const string combinations[NUMBER_OF_COMBINATIONS];
    vector<const Card*> comb_cards;
    vector<const Card*> kicker;
};

class Evaluator
{
public:

    Evaluator(Cards_on_table *cards);
    ~Evaluator();

    void get_strength(Hand_strength *strength);
    void get_strength(Pocket_cards *pocket, Cards_on_table *community,
                            Hand_strength *strength);

    void get_win_list(vector<Hand_strength> &hands,
                      vector<vector<Hand_strength>> &winlist);


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
    //int number_of_cards_in_evaluator;
    //int number_of_cards_in_hand;
    //vector<const Card*> current_hand, card_on_table, players_cards;
    Cards_on_table *community_cards;
    vector<const Card*> all_cards;
};

#endif // EVALUATOR_H
