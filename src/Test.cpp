/*
 * Created by MaximKa on 12.04.2015
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
    deck = new Deck_of_cards();
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
    output << deck->get_cards_in_deck() << '\n';
    output << deck->next_card()->get_full_name() << '\n';
    output << deck->next_card()->get_face() << '\n';
    output << deck->get_cards_in_deck() << '\n';
}

void Test::check_combinations()
{
    Pocket_cards pc;
    Cards_on_table cot;
    Evaluator evaluator(&cot);
    Hand_strength hs;
    long long int counter = 0;
    long long int results[Hand_strength::NUMBER_OF_COMBINATIONS] = {0};

    for (int a = 0; a < Deck_of_cards::DECK_SIZE; ++a) {
        for (int b = a + 1; b < Deck_of_cards::DECK_SIZE; ++b) {
            for (int c = b + 1; c < Deck_of_cards::DECK_SIZE; ++c) {
                for (int d = c + 1; d < Deck_of_cards::DECK_SIZE; ++d) {
                    for (int e = d + 1; e < Deck_of_cards::DECK_SIZE; ++e) {
                        for (int f = e + 1; f < Deck_of_cards::DECK_SIZE; ++f) {;
                            for (int g = f + 1; g < Deck_of_cards::DECK_SIZE; ++g) {
                                pc.set_card(deck->deck[a]);
                                pc.set_card(deck->deck[b]);
                                cot.cards_on_table.push_back(deck->deck[c]);
                                cot.cards_on_table.push_back(deck->deck[d]);
                                cot.cards_on_table.push_back(deck->deck[e]);
                                cot.cards_on_table.push_back(deck->deck[f]);
                                cot.cards_on_table.push_back(deck->deck[g]);
                                evaluator.get_strength(&pc, &hs);
                                ++results[hs.get_combination()];
                                pc.clear();
                                cot.set_preflop();
                                hs.clear_comb_cards();
                                hs.clear_kicker();
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < Hand_strength::NUMBER_OF_COMBINATIONS; ++i) {
        output << i << " : " << results[i] << std::endl;
    }
    output << counter << std::endl;
}



