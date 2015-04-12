/*
 * Created on 20.03.2015 by MaximKa
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation of DeckOfCards.h
 *
 */

#include <cstdlib>
#include <ctime>

#include "DeckOfCards.h"

DeckOfCards::DeckOfCards()
{
    cards_in_deck = DECK_SIZE;
    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i] = new Card(i / Card::NUMBER_OF_SUIT, i % Card::NUMBER_OF_SUIT);
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
        const Card* buf = deck[i];
        deck[i] = deck[j];
        deck[j] = buf;
    }
}

void DeckOfCards::print_deck() const
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        output << deck[i]->getFullName() << (((i + 1) % 2) ? '\t' : '\n');
    }
}

const Card* DeckOfCards::next_card()
{
    //there should be if(cards_in_deck > 0)
    cards_in_deck--;
    return deck[cards_in_deck];
}







