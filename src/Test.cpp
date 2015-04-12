/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 */

#include "Test.h"

Test::Test()
{
    deck = new DeckOfCards();
}

Test::~Test()
{
    delete deck;
}

void Test::check_shuffle()
{
    deck->print_deck();
    output << "\n\n";
    deck->shuffle();
    deck->print_deck();
}



