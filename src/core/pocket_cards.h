/*
 * Created by Maxim Kolotilin on 21.04.2015
 * e-mail: maxkolmail@gmail.com
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

#include "src/core/deck_of_cards.h"
#include <QObject>

class PocketCards: public QObject
{
public:
    static const int POCKET_SIZE = 2;

    PocketCards(QObject *parent = 0);
    virtual ~PocketCards();

    virtual void set_card(const Card *c);
    virtual void reset_pocket_cards();
    virtual void show_hand();

    // return pointer to constant vector
    const vector<const Card *> *get_hand() const;

protected:
    int cards_in_pocket;
    vector<const Card*> pocket_cards;
};

#endif // POCKET_CARDS_H
