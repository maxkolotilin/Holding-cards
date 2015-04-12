/*
 * Created 20.03.2015 by MaximKa
 *
 * Колода карт
 *
 */
#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

struct card_t {
    unsigned short face;
    unsigned short suit;
};

class DeckOfCards {
    public:
        static const int DECK_SIZE = 52;
        static const int NUMBER_OF_FACE = 13;
        static const int NUMBER_OF_SUIT = 4;
        const char* face[NUMBER_OF_FACE] = { "Ace", "Deuce", "Three", "Four", "Five", "Six",
                               "Seven", "Eight", "Nine", "Ten","Jack", "Queen",
                               "King" };
        const char* suit[NUMBER_OF_SUIT] = { "Hearts", "Diamonds", "Clubs", "Spades" };

        DeckOfCards();
        void shuffle();
        void print_deck();
        //card_t next_card();

    private:
        card_t deck[DECK_SIZE];
        int cards_in_deck;

};

#endif  //DECKOFCARDS_H
