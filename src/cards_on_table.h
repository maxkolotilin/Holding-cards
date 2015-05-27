/*
 * Created by MaximKa on 21.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * This class describes community cards on the table
 *
 */

#ifndef CARD_ON_TABLE_H
#define CARD_ON_TABLE_H

#include "src/deck_of_cards.h"

class Cards_on_table
{
    friend class Test;
public:
    Cards_on_table();
    ~Cards_on_table();

    typedef enum { PREFLOP, FLOP, TURN, RIVER } Round_t;

    void set_preflop();
    void set_flop(Deck_of_cards *deck);
    void set_turn(Deck_of_cards *deck);
    void set_river(Deck_of_cards *deck);
    const vector<const Card*> *get_table_cards() const;
    //==============================================
    //void copyCards(vector<const Card*> *v) const
    //{
    //    v->insert(v->end(), cards_on_table.begin(), cards_on_table.end());
    //}

private:
    Round_t round;
    vector<const Card*> cards_on_table;
};

#endif // CARD_ON_TABLE_H
