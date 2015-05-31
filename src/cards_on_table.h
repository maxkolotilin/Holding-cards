/*
 * Created by MaximKa on 21.04.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This class describes community cards on the table
 *
 */

#ifndef CARD_ON_TABLE_H
#define CARD_ON_TABLE_H

#include "src/deck_of_cards.h"

class Cards_on_table
{
    friend class Test;          // is required for tests

public:
    typedef enum { NONE, PREFLOP, FLOP, TURN, RIVER } Round_t;

    Cards_on_table();
    ~Cards_on_table();

    Round_t set_preflop();
    Round_t set_flop(Deck_of_cards *deck);
    Round_t set_turn(Deck_of_cards *deck);
    Round_t set_river(Deck_of_cards *deck);
    const vector<const Card*> *get_table_cards();

private:
    //Round_t round;
    vector<const Card*> cards_on_table;
};

#endif // CARD_ON_TABLE_H
