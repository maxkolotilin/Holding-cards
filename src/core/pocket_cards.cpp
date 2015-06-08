/*
 * Created by Maxim Kolotilin on 21.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation of pocket_cards.h
 *
 */

#include "pocket_cards.h"

PocketCards::PocketCards(QObject *parent) : QObject(parent)
{
    cards_in_pocket = 0;
    pocket_cards.reserve(POCKET_SIZE);
}

PocketCards::~PocketCards()
{

}

void PocketCards::show_hand()
{

}

void PocketCards::set_card(const Card *c)
{
    if (cards_in_pocket == POCKET_SIZE) {
        output << "Error in pocket_cards: an attempt to add an extra card\n";
    } else {
        pocket_cards.push_back(c);
        cards_in_pocket++;
    }
}

const vector<const Card *> *PocketCards::get_hand() const
{
    return &pocket_cards;
}

void PocketCards::reset_pocket_cards()
{
    pocket_cards.clear();
    cards_in_pocket = 0;
}
