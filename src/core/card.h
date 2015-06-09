/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file describes card
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include "src/core/poker_defs.h"
using std::string;

class Card
{
public:
    typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                   JACK, QUEEN, KING, ACE } face_t;
    typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } suit_t;

    static const int NUMBER_OF_FACES = 13;
    static const int NUMBER_OF_SUITS = 4;

    Card(int face, int suit);
    ~Card();

    void print_card() const;
    void get_values(face_t &face, suit_t &suit) const;

    face_t get_face() const
    {
        return face;
    }
    suit_t get_suit() const
    {
        return suit;
    }
    string get_face_name() const
    {
        return faces[face];
    }
    string get_suit_name() const
    {
        return suits[suit];
    }
    string get_full_name() const
    {
        return get_face_name() + " of " + get_suit_name();
    }

    bool operator < (const Card &c) const
    {
        return get_face() < c.get_face();
    }
    bool operator > (const Card &c) const
    {
        return get_face() > c.get_face();
    }
    bool operator == (const Card &c) const
    {
        return get_face() == c.get_face();
    }

    // next function is required for std::sort()
    static bool greater(const Card *c_1, const Card *c_2);

private:
    face_t face;
    suit_t suit;

    static const string faces[];
    static const string suits[];
    // see strings in card.cpp

};

#endif // CARD_H
