/*
 * Created on 20.03.2015 by MaximKa
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * If you think that this file describes deck of card, you are probably right
 *
 */

#ifndef Deck_of_cards_H
#define Deck_of_cards_H

#include <vector>
#include "card.h"

using std::vector;

class Deck_of_cards {
    friend class Test;     // is required for tests
public:
    static const int DECK_SIZE = 52;

    Deck_of_cards();
    ~Deck_of_cards();
    void shuffle();
    void print_deck() const;         // debug
    int get_cards_in_deck() const
    {
        return cards_in_deck;
    }
    const Card *next_card();

private:
    vector<const Card*> deck;
    int cards_in_deck;
};

#endif  //Deck_of_cards_H
