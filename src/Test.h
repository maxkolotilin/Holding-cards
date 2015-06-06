/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Some tests
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
public:
    Test();
    ~Test();

    void check_shuffle();
    void check_card_functions();
    void check_combinations();

    DeckOfCards* deck;
};

#endif // TEST_H
