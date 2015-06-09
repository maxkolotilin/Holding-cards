/*
 * Created on 20.03.2015 by Maxim Kolotilin
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * If you think that this file describes deck of cards, you are probably right
 *
 */

#ifndef Deck_of_cards_H
#define Deck_of_cards_H

#include <vector>
#include "src/core/card.h"

using std::vector;

class DeckOfCards {
    friend class Test;     // is required for tests

public:
    static const int DECK_SIZE = 52;

    DeckOfCards();
    ~DeckOfCards();

    void shuffle();
    const Card *deal_next_card();
    void print_deck() const;
    int get_current_deck_size() const
    {
        return current_deck_size;
    }

private:
    vector<const Card*> deck;
    int current_deck_size;
};

#endif  //Deck_of_cards_H
