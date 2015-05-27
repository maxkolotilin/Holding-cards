/*
 * Created by MaximKa on 21.04.2015
 *
 * License: none
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
    round = PREFLOP;
}

Cards_on_table::~Cards_on_table() {}

void Cards_on_table::set_preflop()
{
    cards_on_table.clear();
    round = PREFLOP;
}

void Cards_on_table::set_flop(Deck_of_cards *deck)
{
    for (int i = 1; i <= 3; ++i) {
        cards_on_table.push_back(deck->next_card());
    }
    round = FLOP;
}

void Cards_on_table::set_turn(Deck_of_cards *deck)
{
    cards_on_table.push_back(deck->next_card());
    round = TURN;
}

void Cards_on_table::set_river(Deck_of_cards *deck)
{
    cards_on_table.push_back(deck->next_card());
    round = RIVER;
}

const vector<const Card *> *Cards_on_table::get_table_cards() const
{
//    static vector<const Card*> v = cards_on_table;
//    return &v;
    return &cards_on_table;
}


