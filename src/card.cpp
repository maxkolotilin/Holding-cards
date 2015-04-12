/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for card.h
 *
 */

#include "card.h"

Card::Card(int face, int suit)
{
    this->face = (Face_t)face;
    this->suit = (Suit_t)suit;
}

Card::~Card()
{}

void Card::getValues(Face_t &face, Suit_t &suit) const
{
    face = this->face;
    suit = this->suit;
}

void Card::printCard()
{
    output << getFullName().data();
}

