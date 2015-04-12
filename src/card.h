/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * This file describes card
 *
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include "src/poker_defs.h"
using std::string;

class Card
{
public:
    typedef enum { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK,
                   QUEEN, KING} Face_t;
    typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit_t;

    static const int NUMBER_OF_FACE = 13;
    static const int NUMBER_OF_SUIT = 4;
    const string faces[NUMBER_OF_FACE] = { "Ace", "Deuce", "Three", "Four", "Five",
                                                  "Six", "Seven", "Eight", "Nine", "Ten",
                                                  "Jack", "Queen", "King" };
    const string suits[NUMBER_OF_SUIT] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    Card(int face, int suit);
    ~Card();

    void printCard();      //Debug
    void getValues(Face_t &face, Suit_t &suit) const;

    Face_t getFace() const { return face; }
    Suit_t getSuit() const { return suit; }
    string getFaceName() const { return faces[face]; }
    string getSuitName() const { return suits[suit]; }
    string getFullName() const { return getFaceName() + " of " + getSuitName(); }

    bool operator <  (const Card &c) const { return getFace() < c.getFace(); }
    bool operator >  (const Card &c) const { return getFace() > c.getFace(); }
    bool operator == (const Card &c) const { return getFace() == c.getFace(); }

    private:
        Face_t face;
        Suit_t suit;

    //TODO
        /*Card();
          Card(const string str);*/
    // get_pic();   returns pointer to image of card, smth like that

};

#endif // CARD_H
