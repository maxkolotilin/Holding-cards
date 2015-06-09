/*
 * Created by Maxim Kolotilin on 27.05.2015
 * e-mail: maxkolmail@gmail.com
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

Game::Game(CardsOnTable *cards, chips_t min_bet, int interval, QObject *parent)
    : QObject(parent)
{
    deck = new DeckOfCards();
    cards_on_table = cards;
    evaluator = new Evaluator(cards_on_table);

    number_of_played_hands = 0;
    number_of_players = 0;
    // current_deal = 0;
    // current_max_bet = 0;
    game_status = BEGIN;

    this->min_bet = min_bet;
    increase_interval = interval;
}

Game::~Game()
{
    delete deck;
    delete cards_on_table;
    delete evaluator;
    for (player_it player = players.begin(); player != players.end(); ++player) {
        delete *player;
    }
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
            it = players.erase(it);     // return next element
            --it;
        }
    }
}

void Game::set_random_dealer()
{
    int position = rand() % 10;

    int i;
    for (i = 0, dealer = players.begin(); i < position; ++i, ++dealer);
    (*dealer)->set_dealer(true);
}

void Game::set_next_dealer()
{
    (*dealer)->set_dealer(false);
    next_player(dealer);
    (*dealer)->set_dealer(true);
}

void Game::start_new_deal()
{
    ++number_of_played_hands;
    number_of_folded = 0;

    bet_blinds();
    deal_cards();

    round = cards_on_table->set_preflop();
    add_to_pot(start_trading());

    // if 2 or more players - continue deal
    if (number_of_folded != number_of_players - 1) {
        round = cards_on_table->set_flop(deck);
        add_to_pot(start_trading());

        reset_bets();
        if (number_of_folded != number_of_players - 1) {
            round = cards_on_table->set_turn(deck);
            add_to_pot(start_trading());

            reset_bets();
            if (number_of_folded != number_of_players - 1) {
                round = cards_on_table->set_river(deck);
                add_to_pot(start_trading());

                reset_bets();
            }
        }
    }

    winners();
}

chips_t Game::start_trading()
{
    // preparing
    player_it start_player = dealer;
    if (round == CardsOnTable::PREFLOP) {
        // blinds are made, skip players on blinds
        const int PLAYER_AFTER_BLINDS = 3;

        for (int i = 0; i < PLAYER_AFTER_BLINDS; ++i) {
            next_player(start_player);
        }
    } else {
        // postflop
        next_player(start_player);
        current_max_bet = 0;
        size_of_last_raise = 0;

        for (player_it player = players.begin(); player != players.end(); ++player) {
            (*player)->reset_my_bets_in_round();
            (*player)->reset_last_action();
        }
    }

    // start betting round
    int made_decision = 0;
    for (player_it current_player = start_player;
         made_decision < number_of_players; ++made_decision ) {

        if ((*current_player)->is_player_in_game() &&
            (*current_player)->get_last_action().action != Player::ALL_IN) {

            Player::action_t act = (*current_player)->action(current_max_bet,
                                                             size_of_last_raise);
            if (act.valid) {
                add_to_bets(act.amount);
                if (act.action == Player::RAISE || act.action == Player::BET) {
                    start_player = current_player;
                    // reset betting round
                    made_decision = 0;
                    size_of_last_raise = (*current_player)->get_bets_in_round() -
                                         current_max_bet;
                    current_max_bet += size_of_last_raise;
                }
                if (act.action == Player::FOLD) {
                    ++number_of_folded;
                }
            } else {
                output << "Player has returned wrong action\n";
            }
        }
        next_player(current_player);
    }

    return total_bets_in_round;
}

void Game::winners()
{
    // all opponents fold
    if (number_of_folded == number_of_players - 1) {
        // search for winner
        player_it player = players.begin();
        for (; !(*player)->is_player_in_game(); ++player);

        winlist.clear();
        vector<Player*> player_vector(1, *player);
        winlist.push_back(player_vector);
    } else {
    // showdown
        for (player_it player = players.begin(); player != players.end(); ++player) {
            // show cards
            if ((*player)->is_player_in_game()) {
                if (*player != human) {
                    (*player)->show_hand();
                }
                evaluator->check_strength(*player);
            }
        }
        evaluator->get_win_list(players, winlist);
    }
}

void Game::distribute_pot_to_players()
{
    vector<Player*> winners = winlist.front();
    for (vector<Player*>::iterator player = winners.begin();
         player != winners.end(); ++player) {
        (*player)->add_to_stack(pot / winners.size());  // potentional error!
    }
}

void Game::start()
{
    if (number_of_players > 1) {
        game_status = CONTINUE;
        set_random_dealer();
        Player::set_min_bet(min_bet);
        while (game_status == CONTINUE) {
            reset_pot();
            reset_bets();
            deck->shuffle();
            start_new_deal();

            if (number_of_players == 1) {
                game_status = END;
            }

            distribute_pot_to_players();
            end_deal();
            search_for_losers();
            set_next_dealer();

            if (number_of_played_hands % increase_interval == 0) {
                increase_min_bet();
            }
        }
    } else {
        output << "There is no players for game\n";
    }
}

void Game::deal_cards()
{
    player_it player = dealer;
    next_player(player);
    // deal 2 cards by one for each player
    for (int i = 0; i < number_of_players * PocketCards::POCKET_SIZE; ++i) {
        (*player)->set_card(deck->deal_next_card());
        next_player(player);
    }

    human->show_hand();
}

void Game::bet_blinds()
{
    player_it blind = dealer;

    next_player(blind);
    add_to_bets((*blind)->blind(Player::SMALL));
    next_player(blind);
    add_to_bets((*blind)->blind(Player::BIG));

    current_max_bet = min_bet;
    size_of_last_raise = min_bet;
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

void Game::next_player(player_it &player)
{
    ++player;
    // make cycled list
    if (player == players.end()) {
        player = players.begin();
    }
}

void Game::end_deal()
{
    cards_on_table->reset_cards_on_table();
    reset_players();
    reset_bets();
    reset_pot();
}
