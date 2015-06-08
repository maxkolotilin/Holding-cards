/*
 * Created by Maxim Kolotilin on 26.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for player.h
 *
 */

#include "player.h"

// ===================== Player ================================

chips_t Player::min_bet;

const string Player::actions[] = { "","Check", "Fold", "Call", "Bet", "Raise",
                                   "All-in", "Big blind", "Small blind", "Show" };
const string Player::blinds[] = { "Small blind", "Big blind" };

Player::Player(std::string name, int id, chips_t stack, PocketCards *hand,
               QObject *parent) : QObject(parent), name(name), player_id(id)
{
    this->hand = hand;
    strength = new HandStrength();
    this->stack = stack;

    reset_player();
}

Player::~Player()
{
    delete hand;
    delete strength;
}


void Player::reset_player()
{
    reset_last_action();
    hand->reset_pocket_cards();
    strength->reset_hand_strength();

    reset_my_bets_in_round();

    is_in_game = true;
}

void Player::reset_last_action()
{
    last_action = RESET_ACTION;
}

string Player::action_to_string(action_t act)
{
    if (last_action.action == NONE || last_action.action == FOLD ||
        last_action.action == CHECK) {
        return actions[act.action];
    } else {
        return actions[act.action] + " " + std::to_string(act.amount);
    }
}

void Player::set_dealer(bool switcher)
{
    is_dealer = switcher;
}

bool Player::greater(const Player *pl_1, const Player *pl_2)
{
    return *pl_1 > *pl_2;
}

bool Player::operator < (const Player &pl) const
{
    return *(this->strength) < *(pl.strength);
}

bool Player::operator > (const Player &pl) const
{
    return *(this->strength) > *(pl.strength);
}

bool Player::operator == (const Player &pl) const
{
    return *(this->strength) == *(pl.strength);
}

chips_t Player::blind(blind_t type)
{
    if (type) {
        last_action = { true, BIG_BLIND, min_bet };
    } else {
        last_action = { true, SMALL_BLIND, min_bet / 2 };
    }

    return stake(0);
}

chips_t Player::stake(chips_t max_bet_in_round)
{
    if (last_action.valid) {
        // if action is all-in
        if (stack <= last_action.amount) {
            last_action = { true, ALL_IN, stack };
        }
        // if action is check
        if (last_action.action == CALL && last_action.amount == 0) {
            last_action.action = CHECK;
        }
        // if action is bet
        if (last_action.action == RAISE && max_bet_in_round == 0) {
            last_action.action = BET;
        }
        stack -= last_action.amount;
        my_bets_in_round += last_action.amount;

        return last_action.amount;
    } else {
        output << "Wrong action\n";
    }

    return 0;
}

void Player::set_fold()
{
    last_action = { true, FOLD, 0 };

    is_in_game = false;
}

void Player::set_all_in()
{
    last_action = { true, ALL_IN, stack };
}

void Player::set_call(chips_t max_bet_in_round)
{
    last_action = { true, CALL, max_bet_in_round - my_bets_in_round };
}

void Player::set_raise(chips_t max_bet_in_round, chips_t raise_size, chips_t bet)
{
    // min raise == call + raise_size
    if (bet >= max_bet_in_round - my_bets_in_round + raise_size) {
        last_action = { true, RAISE, bet };
    } else {
        last_action = { true, RAISE, max_bet_in_round - my_bets_in_round +
                                     raise_size };
    }
}

// ======================= Human ============================

HumanPlayer::HumanPlayer(std::string name, int id, chips_t stack,
                         PocketCards *hand, QObject *parent)
    : Player(name, id, stack, hand, parent)
{

}

HumanPlayer::~HumanPlayer()
{

}

// ======================= Computer ==============================

ComputerPlayer::ComputerPlayer(std::string name, int id, chips_t stack,
                               const chips_t *pot, const chips_t *total_bets,
                               const CardsOnTable::round_t *round,
                               PocketCards *hand, Evaluator *evaluator,
                               QObject *parent)
    : Player(name, id, stack, hand, parent)
{
    all_cards.reserve(CardsOnTable::CARDS_ON_TABLE_SIZE +
                      PocketCards::POCKET_SIZE - 1);  // 6
    this->pot = pot;
    this->round = round;
    this->evaluator = evaluator;
    total_bets_in_round = total_bets;
}

ComputerPlayer::~ComputerPlayer()
{

}

bool ComputerPlayer::is_hand_in_top_10()
{
    const vector<const Card*>* hand_cards = hand->get_hand();

    // TT, JJ, QQ, KK, AA
    if (*(hand_cards->front()) == *(hand_cards->back()) &&
        hand_cards->front()->get_face() > Card::NINE) {
        return true;
    }
    // AKs, AQs, KQs, AJs,
    if (hand_cards->front()->get_suit() ==
        hand_cards->back()->get_suit()) {
        switch (hand_cards->front()->get_face() +
                hand_cards->back()->get_face())
        {
            case Card::ACE + Card::KING:
            case Card::ACE + Card::QUEEN:
            case Card::ACE + Card::JACK:
            //case Card::KING + Card::QUEEN:  // equals to previous line
                return true;
            default:
                break;
        }
    }
    // AKo
    if (hand_cards->front()->get_face() +
        hand_cards->back()->get_face() ==
        Card::ACE + Card::KING) {
        return true;
    }

    return false;
}

bool ComputerPlayer::is_hand_in_top_21()
{
    const vector<const Card*>* hand_cards = hand->get_hand();

    // 88, 99
    if (*(hand_cards->front()) == *(hand_cards->back()) &&
        hand_cards->front()->get_face() > Card::SEVEN) {
        return true;
    }
    // ATs, KJs, QJs, KTs, QTs, A9s
    if (hand_cards->front()->get_suit() ==
        hand_cards->back()->get_suit()) {
        switch (hand_cards->front()->get_face() +
                hand_cards->back()->get_face())
        {
            case Card::ACE + Card::TEN:
            case Card::QUEEN + Card::JACK:
            case Card::QUEEN + Card::TEN:
            // other 3 combinations is equal to previous 3 lines
                return true;
            default:
                break;
        }
    }
    // AQo
    if (hand_cards->front()->get_face() +
        hand_cards->back()->get_face() ==
        Card::ACE + Card::QUEEN) {
        return true;
    }
    // AJo, KQo
    if (hand_cards->front()->get_face() +
        hand_cards->back()->get_face() ==
        Card::ACE + Card::JACK) {
        return true;
    }

    return false;
}

bool ComputerPlayer::is_connectors()
{
    const vector<const Card*>* hand_cards = hand->get_hand();

    if (abs(hand_cards->front()->get_face() - hand_cards->back()->get_face()) == 1) {
        return true;
    }

    return false;
}

bool ComputerPlayer::is_suited()
{
    const vector<const Card*>* hand_cards = hand->get_hand();

    if (hand_cards->front()->get_suit() == hand_cards->back()->get_suit()) {
        return true;
    }

    return false;
}

void ComputerPlayer::current_combination()
{
    evaluator->get_strength(this);
}

int ComputerPlayer::count_outs()
{
    outs = 0;
    is_flush_dro = false;
    is_straight_dro = false;
    is_gutshot = false;

    all_cards.clear();
    copy_to_all_cards(evaluator->get_communitu_cards()->get_table_cards());
    copy_to_all_cards(hand->get_hand());

    // sort cards descending
    std::sort(all_cards.begin(), all_cards.end(), Card::greater);

    if (!is_flush_dro) {
        if ((is_flush_dro = check_flush_dro())) {
            outs += FLUSH_DRO_OUTS;
        }
    } else {
        outs += FLUSH_DRO_OUTS;
    }
    if (!is_straight_dro) {
        if ((is_straight_dro = check_straight_dro())) {
            outs += STRAIGHT_DRO_OUTS;
        }
    } else {
        outs += STRAIGHT_DRO_OUTS;
    }
    if (!is_gutshot) {
        if ((is_gutshot = check_gutshot())) {
            outs += GUTSHOT_OUTS;
        }
    } else {
        outs += GUTSHOT_OUTS;
    }

    // remove 2 cards that we have counted twice
    if (is_flush_dro && is_straight_dro) {
        outs -= 2;
    }
    // remove card that we have counted twice
    if (is_flush_dro && is_gutshot) {
        outs -= 1;
    }

    // unlucky,don't have any combination
    if (strength->get_combination() == HandStrength::HIGH_CARD) {
        outs += HIGH_CARD_OUTS * PocketCards::POCKET_SIZE;
    }

    // pair => three of a kind
    if (strength->get_combination() == HandStrength::PAIR) {
        outs += PAIR_OUTS;
    }

    // two pairs => three of a kind
    if (strength->get_combination() == HandStrength::TWO_PAIRS) {
        outs += TWO_PAIRS_OUTS;
    }

    // three of a kind => four of a kind
    if (strength->get_combination() == HandStrength::TREE_OF_A_KIND) {
        outs += THREE_TO_FOUR_OUTS;
    }

    // three of a kind => full house
    if (strength->get_combination() == HandStrength::TREE_OF_A_KIND) {
        if (*round == CardsOnTable::FLOP) {
            // 6
            outs += HIGH_CARD_OUTS * (PocketCards::POCKET_SIZE +
                    CardsOnTable::CARDS_ON_FLOP - Evaluator::THREE_OF_A_KIND_SIZE);
        } else {
            // 9
            outs += HIGH_CARD_OUTS * (PocketCards::POCKET_SIZE +
                    CardsOnTable::CARDS_ON_TURN - Evaluator::THREE_OF_A_KIND_SIZE);
        }
    }

    return outs;
}

bool ComputerPlayer::check_flush_dro()
{
    // count same suits for flush-dro
    int suit_counter[Card::NUMBER_OF_SUITS] = {0};
    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
        if (++suit_counter[(*card)->get_suit()] == Evaluator::FLUSH_SIZE - 1) {
            is_flush_dro = true;

            return true;
        }
    }

    return false;
}

bool ComputerPlayer::check_straight_dro()
{
    // check two-side straight-dro
    int last_face = -1, counter = 0;
    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
        // ignore cards of same face
        if (last_face == (*card)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*card)->get_face()) {
            counter = 1;
        } else {
            if (++counter == Evaluator::STRAIGHT_SIZE - 1) {
                break;
            }
        }
        last_face = (*card)->get_face();
    }

    // check one-side straight-dro (outs equals to gutshot)
    // in top straight
    if (counter == Evaluator::STRAIGHT_SIZE - 1 && last_face == Card::JACK) {
        is_gutshot = true;

        return false;
    }
    // in "wheel" 4-3-2-A
    if (all_cards.front()->get_face() == Card::ACE &&
        counter == Evaluator::STRAIGHT_SIZE - 2 && last_face == Card::TWO) {
        is_gutshot = true;

        return false;
    }

    return true;
}

bool ComputerPlayer::check_gutshot()
{
    // How it works on example: we have A-Q-J-9-8-2. It is gutshot,
    // but check_gutshot() from begin return false. There are 2 holes:
    // from Q and from 9. check_gutshot() from Q returns true.

    int last_face = -1;

    // check gutshot from begin
    if (check_gutshot_helper(all_cards.begin(), all_cards.end())) {
        return true;
    }

    // check gutshot from holes
    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card)
    {
        // if it is hole...
        if (last_face - 2 == (*card)->get_face()) {
            if (check_gutshot_helper(card, all_cards.end())) {
                return true;
            }
        }
        last_face = (*card)->get_face();
    }

    return false;
}

bool ComputerPlayer::check_gutshot_helper(card_it begin, card_it end)
{
    if (end - begin < Evaluator::STRAIGHT_SIZE - 1) {
        return false;
    }

    int last_face = -1, counter = 0;
    bool hole = false;

    for (card_it card = begin; card != end; ++card) {
        // ignore cards of same face
        if (last_face == (*card)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*card)->get_face()) {
            // check hole
            if (!hole && last_face - 2 == (*card)->get_face()) {
                hole = true;
                ++counter;
            } else {
                counter = 1;
            }
        } else {
            if (++counter == Evaluator::STRAIGHT_SIZE - 1) {
                return true;
            }
        }
        last_face = (*card)->get_face();
    }

    // check gutshot in "wheel"
    // 5-3-2-A, 5-4-2-A
    if (all_cards.front()->get_face() == Card::ACE &&
        last_face == Card::TWO && hole && Evaluator::STRAIGHT_SIZE - 2) {
        return true;
    }
    // 5-4-3-A
    if (all_cards.front()->get_face() == Card::ACE &&
        Evaluator::STRAIGHT_SIZE - 2 && last_face == Card::THREE) {
        return true;
    }

    return false;
}

bool ComputerPlayer::check_pot_odds(chips_t bet)
{
    const double TO_PERCENTS = 100.0;
    const int FIRST_BOARD = 3, SECOND_BOARD = 12;

    int combination_odds;
    if (outs <= FIRST_BOARD) {
        combination_odds = outs * 2;
    } else if (outs >= SECOND_BOARD) {
        combination_odds = outs * 2 + 2;
    } else {
        combination_odds = outs * 2 + 1;
    }

    if (bet * TO_PERCENTS / (bet + *pot + *total_bets_in_round) <= combination_odds) {
        return true;
    }

    return false;
}

Player::action_t ComputerPlayer::action(chips_t max_bet_in_round, chips_t raise_size)
{
    const double MAX_LIMIT_ON_PREFLOP = 0.1;
    const double MID_LIMIT_ON_PREFLOP = 0.05;
    const double MIN_LIMIT_ON_PREFLOP = 0.03;
    const double MAX_LIMIT_ON_POSTFLOP = 0.5;
    const double MIN_LIMIT_ON_POSTFLOP = 0.1;

    if (is_in_game) {
        //this->max_bet_in_round = max_bet_in_round;

        if(*round == CardsOnTable::PREFLOP) {

            if(is_hand_in_top_10()) {
                if ((double)(max_bet_in_round + 2 * raise_size) / stack <
                    MAX_LIMIT_ON_PREFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + 2 * raise_size - my_bets_in_round);
                } else if ((double)(max_bet_in_round + raise_size) / stack <
                           MAX_LIMIT_ON_PREFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + raise_size - my_bets_in_round);
                } else {
                    set_call(max_bet_in_round);
                }

            } else if(is_hand_in_top_21()) {
                if ((double)(max_bet_in_round + raise_size) / stack <
                    MID_LIMIT_ON_PREFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + raise_size - my_bets_in_round);
                } else {
                    set_call(max_bet_in_round);
                }

            } else if(is_connectors() || is_suited()) {
                if ((double)max_bet_in_round / stack < MIN_LIMIT_ON_PREFLOP) {
                    set_call(max_bet_in_round);
                } else {
                    set_fold();
                }

            } else {
                set_fold();
            }

        } else {   // Postflop

            current_combination();
            count_outs();
            // if we have strong hand...
            if (strength->get_combination() > HandStrength::FLUSH) {
                if (max_bet_in_round == 0) {
                    // make bet
                    set_raise(max_bet_in_round, raise_size,
                              3 * min_bet);
                } else if ((double)(max_bet_in_round + 3 * raise_size) / stack <
                    MAX_LIMIT_ON_POSTFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + 3 * raise_size - my_bets_in_round);
                } else if ((double)(max_bet_in_round + raise_size) / stack <
                           MAX_LIMIT_ON_POSTFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + raise_size - my_bets_in_round);
                } else {
                    set_call(max_bet_in_round);
                }

            } else if (strength->get_combination() > HandStrength::PAIR) {
                if (max_bet_in_round == 0) {
                    // make bet
                    set_raise(max_bet_in_round, raise_size,
                              min_bet);
                } else if ((double)(max_bet_in_round + raise_size) / stack <
                    MIN_LIMIT_ON_POSTFLOP) {
                    set_raise(max_bet_in_round, raise_size,
                              max_bet_in_round + raise_size - my_bets_in_round);
                } else {
                    if (check_pot_odds(max_bet_in_round - my_bets_in_round)) {
                        set_call(max_bet_in_round);
                    } else {
                        set_fold();
                    }
                }

            } else {
                if (check_pot_odds(max_bet_in_round - my_bets_in_round)) {
                    set_call(max_bet_in_round);
                } else {
                    set_fold();
                }
            }

        }

        stake(max_bet_in_round);
    }

    return last_action;
}
