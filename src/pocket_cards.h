/*
 * Created by MaximKa on 21.04.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This class describes player's hand
 *
 */

#ifndef POCKET_CARDS_H
#define POCKET_CARDS_H

#include "src/deck_of_cards.h"

class Player;

class Pocket_cards
{
    //friend class Player;

public:
    Pocket_cards();
    ~Pocket_cards();

    void set_card(const Card *c);
    const vector<const Card *> *get_hand() const;
    void clear();

    //void copyCards(std::vector<Card> *v) const { v->insert(v->end(), cards.begin(), cards.end()); };

private:
    int cards_in_pocket;
    vector<const Card*> pocket_cards;
};

#endif // POCKET_CARDS_H
