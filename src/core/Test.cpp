/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Some tests
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
    output << "\n\n";
}

void Test::check_card_functions()
{
    output << deck->get_current_deck_size() << '\n';
    output << deck->deal_next_card()->get_full_name() << '\n';
    output << deck->deal_next_card()->get_face() << '\n';
    output << deck->get_current_deck_size() << '\n';
}

void Test::check_combinations()
{
    PocketCards pc;
    CardsOnTable cot;
    Evaluator evaluator(&cot);
    HandStrength hs;
    long long int counter = 0;
    long long int results[HandStrength::NUMBER_OF_COMBINATIONS] = {0};

    for (int a = 0; a < DeckOfCards::DECK_SIZE; ++a) {
        for (int b = a + 1; b < DeckOfCards::DECK_SIZE; ++b) {
            for (int c = b + 1; c < DeckOfCards::DECK_SIZE; ++c) {
                for (int d = c + 1; d < DeckOfCards::DECK_SIZE; ++d) {
                    for (int e = d + 1; e < DeckOfCards::DECK_SIZE; ++e) {
                        for (int f = e + 1; f < DeckOfCards::DECK_SIZE; ++f) {;
                            for (int g = f + 1; g < DeckOfCards::DECK_SIZE; ++g) {
                                pc.set_card(deck->deck[a]);
                                pc.set_card(deck->deck[b]);
                                cot.cards_on_table.push_back(deck->deck[c]);
                                cot.cards_on_table.push_back(deck->deck[d]);
                                cot.cards_on_table.push_back(deck->deck[e]);
                                cot.cards_on_table.push_back(deck->deck[f]);
                                cot.cards_on_table.push_back(deck->deck[g]);
                                evaluator.get_strength(&pc, &hs);
                                ++results[hs.get_combination()];
                                pc.reset_pocket_cards();
                                cot.set_preflop();
                                hs.clear_combination_cards();
                                hs.clear_kicker_cards();
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < HandStrength::NUMBER_OF_COMBINATIONS; ++i) {
        output << i << " : " << results[i] << std::endl;
    }
    output << counter << std::endl;
}



