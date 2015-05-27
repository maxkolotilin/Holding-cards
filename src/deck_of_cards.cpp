/*
 * Created on 20.03.2015 by MaximKa
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation of Deck_of_cards.h
 *
 */

#include <cstdlib>
#include <ctime>

#include "deck_of_cards.h"

Deck_of_cards::Deck_of_cards()
{
    cards_in_deck = DECK_SIZE;
    deck.reserve(52);
    for (int i = 0; i < DECK_SIZE; ++i) {
        deck.push_back(new Card(i / Card::NUMBER_OF_SUIT,
                                i % Card::NUMBER_OF_SUIT));
    }
    srand(time(0));
}

Deck_of_cards::~Deck_of_cards()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        delete deck[i];
    }
}

void Deck_of_cards::shuffle()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        int j = rand() % DECK_SIZE;
        std::swap(deck[i], deck[j]);
    }
    cards_in_deck = DECK_SIZE;
    //std::random_shuffle(deck.begin(), deck.end());
}

void Deck_of_cards::print_deck() const
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        output << deck[i]->get_full_name() << (((i + 1) % 2) ? '\t' : '\n');
    }
}

const Card* Deck_of_cards::next_card()
{
    //there should be if(cards_in_deck > 0)
    return deck[--cards_in_deck];
}
