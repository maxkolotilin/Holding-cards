/*
 * Created by MaximKa on 21.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation of pocket_cards.h
 *
 */

#include "pocket_cards.h"

Pocket_cards::Pocket_cards()
{
    cards_in_pocket = 0;
    pocket_cards.reserve(2);
}

Pocket_cards::~Pocket_cards() {}

void Pocket_cards::set_card(const Card *c)
{
    if (cards_in_pocket == 2) {    //Is it needed?
        output << "Error in pocket_cards\n";
    } else {
        pocket_cards.push_back(c);
        cards_in_pocket++;
    }
}

const vector<const Card *> * Pocket_cards::get_hand() const
{
//    static vector<const Card*> v = pocket_cards;
//    return &v;
    return &pocket_cards;
}

void Pocket_cards::clear()
{
    pocket_cards.clear();
    cards_in_pocket = 0;
}
