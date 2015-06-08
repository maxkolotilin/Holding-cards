/*
 * Created by Maxim Kolotilin on 21.04.2015
 * e-mail: maxkolmail@gmail.com
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

CardsOnTable::CardsOnTable(QObject *parent) : QObject(parent)
{
    cards_on_table.reserve(CARDS_ON_TABLE_SIZE);
}

CardsOnTable::~CardsOnTable()
{

}

CardsOnTable::round_t CardsOnTable::set_preflop()
{
    return PREFLOP;
}

CardsOnTable::round_t CardsOnTable::set_flop(DeckOfCards *deck)
{
    for (int i = 0; i < CARDS_ON_FLOP; ++i) {
        cards_on_table.push_back(deck->deal_next_card());
    }

    return FLOP;
}

CardsOnTable::round_t CardsOnTable::set_turn(DeckOfCards *deck)
{
    for (int i = CARDS_ON_FLOP; i < CARDS_ON_TURN; ++i) {
        cards_on_table.push_back(deck->deal_next_card());
    }

    return TURN;
}

CardsOnTable::round_t CardsOnTable::set_river(DeckOfCards *deck)
{
    for (int i = CARDS_ON_TURN; i < CARDS_ON_RIVER; ++i) {
        cards_on_table.push_back(deck->deal_next_card());
    }

    return RIVER;
}

CardsOnTable::round_t CardsOnTable::reset_cards_on_table()
{
    cards_on_table.clear();

    return NONE;
}

const vector<const Card *> *CardsOnTable::get_table_cards() const
{
    return &cards_on_table;
}
