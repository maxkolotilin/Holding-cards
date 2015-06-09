/*
 * Created by Maxim Kolotilin on 21.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This class describes community cards on the table
 *
 */

#ifndef CARD_ON_TABLE_H
#define CARD_ON_TABLE_H

#include "src/core/deck_of_cards.h"
#include <QObject>

class CardsOnTable : public QObject
{
    friend class Test;          // is required for tests

public:
    typedef enum { NONE, PREFLOP, FLOP, TURN, RIVER } round_t;
    static const int CARDS_ON_TABLE_SIZE = 5;
    static const int CARDS_ON_FLOP = 3;
    static const int CARDS_ON_TURN = 4;
    static const int CARDS_ON_RIVER = 5;

    CardsOnTable(QObject *parent = 0);
    virtual ~CardsOnTable();

    virtual round_t set_preflop();
    virtual round_t set_flop(DeckOfCards *deck);
    virtual round_t set_turn(DeckOfCards *deck);
    virtual round_t set_river(DeckOfCards *deck);
    virtual round_t reset_cards_on_table();

    // return pointer to constant vector
    const vector<const Card*> *get_table_cards() const;

protected:
    vector<const Card*> cards_on_table;
};

#endif // CARD_ON_TABLE_H
