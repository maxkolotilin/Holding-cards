/*
 * Created on 20.03.2015 by Maxim Kolotilin
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for DeckOfCards.h
 *
 */

#include <cstdlib>
#include <ctime>

#include "deck_of_cards.h"

DeckOfCards::DeckOfCards()
{
    current_deck_size = DECK_SIZE;
    deck.reserve(DECK_SIZE);

    for (int i = 0; i < DECK_SIZE; ++i) {
        deck.push_back(new Card(i / Card::NUMBER_OF_SUITS,
                                i % Card::NUMBER_OF_SUITS));
    }
    srand(time(0));
}

DeckOfCards::~DeckOfCards()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        delete deck[i];
    }
}

void DeckOfCards::shuffle()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        int j = rand() % DECK_SIZE;
        std::swap(deck[i], deck[j]);
    }
    current_deck_size = DECK_SIZE;

    // std::random_shuffle(deck.begin(), deck.end());
}

void DeckOfCards::print_deck() const
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        output << deck[i]->get_full_name() << (((i + 1) % 2) ? '\t' : '\n');
    }
    // output is defined in poker_defs.h
}

const Card* DeckOfCards::deal_next_card()
{
    return deck[--current_deck_size];
}
