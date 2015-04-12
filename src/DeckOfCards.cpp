#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "DeckOfCards.h"

DeckOfCards::DeckOfCards()
{
    cards_in_deck = DECK_SIZE;
    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i].face = i / NUMBER_OF_SUIT;
        deck[i].suit = i % NUMBER_OF_SUIT;
    }
    srand(time(0));
}

void DeckOfCards::shuffle()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        int j = rand() % DECK_SIZE;
        card_t buf = deck[i];
        deck[i] = deck[j];
        deck[j] = buf;
    }
}

void DeckOfCards::print_deck()
{
    for (int i = 0; i < DECK_SIZE; ++i) {
        cout << right << setw(5) << face[deck[i].face] << " of "
             << left << setw(8) << suit[deck[i].suit] <<
             (((i + 1) % 2) ? '\t' : '\n');
    }
}







