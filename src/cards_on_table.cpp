/*
 * Created by MaximKa on 21.04.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation of cards_on_table.h
 *
 */

#include "cards_on_table.h"

Cards_on_table::Cards_on_table()
{
    cards_on_table.reserve(5);
    //round = NONE;
}

Cards_on_table::~Cards_on_table()
{

}

Cards_on_table::Round_t Cards_on_table::set_preflop()
{
    cards_on_table.clear();
    return PREFLOP;
}

Cards_on_table::Round_t Cards_on_table::set_flop(Deck_of_cards *deck)
{
    for (int i = 1; i <= 3; ++i) {
        cards_on_table.push_back(deck->next_card());
    }
    return FLOP;
}

Cards_on_table::Round_t Cards_on_table::set_turn(Deck_of_cards *deck)
{
    cards_on_table.push_back(deck->next_card());
    return TURN;
}

Cards_on_table::Round_t Cards_on_table::set_river(Deck_of_cards *deck)
{
    cards_on_table.push_back(deck->next_card());
    return RIVER;
}

const vector<const Card *> *Cards_on_table::get_table_cards()
{
    return &cards_on_table;
}
