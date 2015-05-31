/*
 * Created by MaximKa on 12.04.2015
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
#include "src/poker_defs.h"
using std::string;

class Card
{
public:
    typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                   JACK, QUEEN, KING, ACE } Face_t;
    typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit_t;

    static const int NUMBER_OF_FACE = 13;
    static const int NUMBER_OF_SUIT = 4;

    Card(int face, int suit);
    ~Card();

    void print_card() const;      // Debug
    void get_values(Face_t &face, Suit_t &suit) const;

    Face_t get_face() const
    {
        return face;
    }
    Suit_t get_suit() const
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
        Face_t face;
        Suit_t suit;

        static const string faces[NUMBER_OF_FACE];
        static const string suits[NUMBER_OF_SUIT];
        // see strings in card.cpp

};

#endif // CARD_H
