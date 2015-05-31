/*
 * Created by MaximKa on 12.04.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for card.h
 *
 */

#include "card.h"

const string Card::faces[] = { "Deuce", "Three", "Four", "Five",
                               "Six", "Seven", "Eight", "Nine", "Ten",
                               "Jack", "Queen", "King", "Ace" };
const string Card::suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

Card::Card(int face, int suit)
{
    this->face = (Face_t)face;
    this->suit = (Suit_t)suit;
}

Card::~Card()
{}

void Card::get_values(Face_t &face, Suit_t &suit) const
{
    face = this->face;
    suit = this->suit;
}

void Card::print_card() const
{
    output << get_full_name();
}

bool Card::greater(const Card *c_1, const Card *c_2)
{
    return *c_1 > *c_2;
}
