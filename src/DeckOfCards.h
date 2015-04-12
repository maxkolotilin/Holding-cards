/*
 * Created on 20.03.2015 by MaximKa
 *
 * It's a part of Texas Hold'em project
 *
 * If you think that this file describes deck of card, you are probably right
 *
 */

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include "card.h"

class DeckOfCards {
public:
    static const int DECK_SIZE = 52;

    DeckOfCards();
    ~DeckOfCards();
    void shuffle();
    void print_deck() const;      //debug
    int getNumberOfCardsInDeck() { return cards_in_deck; }
    const Card *next_card();

private:
    const Card* deck[DECK_SIZE];
    int cards_in_deck;
};

#endif  //DECKOFCARDS_H
