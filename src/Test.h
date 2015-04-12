/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 */

#ifndef TEST_H
#define TEST_H

#include "src/card.h"
#include "src/DeckOfCards.h"

class Test
{
public:
    Test();
    ~Test();
    void check_shuffle();

    DeckOfCards* deck;
};

#endif // TEST_H
