/*
 * Created by MaximKa on 27.05.2015
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for game.h
 */

#include "game.h"
#include <ctime>

Game::Game(Cards_on_table *cards, chips_t min_bet)
{
    deck = new Deck_of_cards();
    cards_on_table = cards;
    evaluator = new Evaluator(cards_on_table);

    number_of_played_hands = 0;
    number_of_players = 0;
    current_deal = 0;
    current_max_bet = 0;
    game_status = BEGIN;

    this->min_bet = min_bet;
}

Game::~Game()
{
    delete deck;
    delete cards_on_table;
    delete evaluator;
}

void Game::add_player(Player *pl)
{
    players.push_back(pl);
    ++number_of_players;
}

void Game::search_for_losers()
{
    for (player_it it = players.begin(); it != players.end(); ++it) {
        if ((*it)->get_stack() == 0) {
            --number_of_players;
            delete *it;
            it = players.erase(it);
            --it;
        }
    }
}

void Game::set_random_dealer()
{
    int position = rand() % 10;

    int i;
    for (i = 0, dealer = players.begin(); i < position; ++i, ++dealer);
}

void Game::start_new_deal()
{
    ++number_of_played_hands;
    pot = 0;
    number_of_folded = 0;

    deal_cards();

    round = cards_on_table->set_preflop();
    pot += start_trading();

    // if 2 or more players - continue deal
    if (number_of_folded != number_of_players - 1) {
        round = cards_on_table->set_flop(deck);
        pot += start_trading();

        if (number_of_folded != number_of_players - 1) {
            round = cards_on_table->set_turn(deck);
            pot += start_trading();

            if (number_of_folded != number_of_players - 1) {
                round = cards_on_table->set_river(deck);
                pot += start_trading();
            }
        }
    }

    winners();
    search_for_losers();

    ++dealer;
}

chips_t Game::start_trading()
{
    bets = 0;
    current_max_bet = 0;

    player_it start_player;
    if (round == Cards_on_table::PREFLOP) {
        player_it blinds = dealer;
        bets = (*++blinds)->blind(Player::SMALL_BLIND);
        bets = (*++blinds)->blind(Player::BIG_BLIND);

        start_player = ++blinds;

        current_max_bet = min_bet;
    } else {
        start_player = dealer;
        ++start_player;
    }

    int made_decision = 0;
    for (player_it current_player = start_player;
         made_decision < number_of_players; ++made_decision ) {
        Player::action_t act = (*current_player)->action(current_max_bet);
        if (act.valid) {
            bets += act.amount;
            if (act.action == Player::RAISE) {
                start_player = current_player;
                made_decision = 0;
                current_max_bet = act.amount;
            }
            if (act.action == Player::FOLD) {
                ++number_of_folded;
            }
        } else {
            output << "Wrong action\n";
        }
        // increment current_player
        ++current_player;
        // make cycled list
        if (current_player == players.end()) {
            current_player = players.begin();
        }
    }

    return bets;
}

void Game::winners()
{
    if (number_of_folded == number_of_players - 1) {
        player_it player = players.begin();
        for (; (*player)->get_last_action().action == Player::NONE; ++player);
        (*player)->get_won_bank(pot);
    } else {
        for (player_it player = players.begin(); player != players.end();
             ++player) {
            if ((*player)->get_last_action().action != Player::NONE) {
                evaluator->get_strength((*player)->get_hand(),
                                        (*player)->get_strength());
            }
        }

        evaluator->get_win_list(players, winlist);
        vector<Player*> winners = winlist.front();
        int number_of_winners = winners.size();
        for (vector<Player*>::iterator player = winners.begin();
             player != winners.end(); ++player) {
            (*player)->get_won_bank(pot / number_of_winners);  // potentional error!
        }
    }
}

void Game::game_logic()
{
    if (number_of_players > 1) {
        game_status = CONTINUE;
        set_random_dealer();
        while (game_status == CONTINUE) {
            start_new_deal();

            if (number_of_players == 1) {
                game_status = END;
            }

            reset_players();
        }
    } else {
        output << "There is no players for game\n";
    }
}

void Game::deal_cards()
{
    player_it player = dealer;
    ++player;
    // deal 2 cards for each player
    for (int i = 0; i < number_of_players * 2; ++i) {
        (*player)->set_card(deck->next_card());
        ++player;
        // make cycled list
        if (player == players.end()) {
            player = players.begin();
        }
    }
}

void Game::reset_players()
{
    for (player_it player = players.begin(); player != players.end(); ++player) {
        (*player)->reset_player();
    }
}

void Game::increase_min_bet()
{
    min_bet <<= 1;  // *= 2;
    Player::set_min_bet(min_bet);
}
