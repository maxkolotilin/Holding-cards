/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 */

#ifndef TEST_H
#define TEST_H

#include "src/card.h"
#include "src/deck_of_cards.h"
#include "src/cards_on_table.h"
#include "src/evaluator.h"
#include "src/pocket_cards.h"
#include "src/poker_defs.h"

class Test
{
    friend class Deck_of_cards;
    friend class Pocket_cards;
    friend class Evaluator;
    friend class Hand_strength;
    friend class Cards_on_table;
public:
    Test();
    ~Test();
    void check_shuffle();
    void check_card_functions();
    void check_combinations();
    Deck_of_cards* deck;
};

#endif // TEST_H
