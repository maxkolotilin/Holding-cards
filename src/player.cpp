/*
 * Created by MaximKa on 26.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for player.h
 *
 */

#include "player.h"

Player::Player(int id) : player_id(id)
{
    next_action.valid = false;
    last_action = {false, Player::NONE, 0};
    sitout = false;
    hand = new Pocket_cards();
    strength = new Hand_strength();
}

/*virtual*/ Player::~Player()
{
    delete hand;
    delete strength;
}

chips_t Player::blind(blind_t type)
{
    if (type == BIG_BLIND) {
        stack -= *min_bet;
        return *min_bet;
    } else {
        stack -= *min_bet / 2;
        return *min_bet / 2;
    }
}

chips_t Player::bet(action_t action)
{
    if (action.valid) {
        stack -= action.amount;
        return action.amount;
    }

    return 0;
}

HumanPlayer::HumanPlayer(int id) : Player(id)
{

}

HumanPlayer::~HumanPlayer()
{

}

ComputerPlayer::ComputerPlayer(int id, const chips_t *pot) : Player(id)
{
    all_cards.reserve(6);
    this->pot = pot;
}

ComputerPlayer::~ComputerPlayer()
{

}

bool ComputerPlayer::check_top_10_hands()
{
    const vector<const Card*>* hand_ptr = hand->get_hand();
    // TT, JJ, QQ, KK, AA
    if (*(hand_ptr->front()) == *(hand_ptr->back()) &&
        hand_ptr->front()->get_face() > Card::NINE) {
        return true;
    }
    // AKs, AQs, KQs, AJs,
    if (hand_ptr->front()->get_suit() ==
        hand_ptr->back()->get_suit()) {
        switch (hand_ptr->front()->get_face() +
                hand_ptr->back()->get_face())
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
    if (hand_ptr->front()->get_face() +
        hand_ptr->back()->get_face() ==
        Card::ACE + Card::KING) {
        return true;
    }

    return false;
}

bool ComputerPlayer::check_top_21_hands()
{
    const vector<const Card*>* hand_ptr = hand->get_hand();
    // 88, 99
    if (*(hand_ptr->front()) == *(hand_ptr->back()) &&
        hand_ptr->front()->get_face() > Card::SEVEN) {
        return true;
    }
    // ATs, KJs, QJs, KTs, QTs, A9s
    if (hand_ptr->front()->get_suit() ==
        hand_ptr->back()->get_suit()) {
        switch (hand_ptr->front()->get_face() +
                hand_ptr->back()->get_face())
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
    // AQo, AJo, KQo
    if (hand_ptr->front()->get_face() +
        hand_ptr->back()->get_face() ==
        Card::ACE + Card::QUEEN) {
        return true;
    }
    if (hand_ptr->front()->get_face() +
        hand_ptr->back()->get_face() ==
        Card::ACE + Card::JACK) {
        return true;
    }

    return false;
}

bool ComputerPlayer::check_connectors()
{
    const vector<const Card*>* hand_ptr = hand->get_hand();
    if (abs(hand_ptr->front()->get_face() - hand_ptr->back()->get_face()) == 0) {
        return true;
    }

    return false;
}

bool ComputerPlayer::check_suited()
{
    const vector<const Card*>* hand_ptr = hand->get_hand();
    if (hand_ptr->front()->get_suit() == hand_ptr->back()->get_suit()) {
        return true;
    }

    return false;
}

void ComputerPlayer::current_combination(Evaluator &evaluator)
{
    evaluator.get_strength(strength);
}

int ComputerPlayer::count_outs(Evaluator &evaluator,
                               Cards_on_table &community_cards)
{
    outs = 0;
    is_flush_dro = false;
    is_straight_dro = false;
    is_gutshot = false;

    copyToAllCards(community_cards.get_table_cards());
    copyToAllCards(hand->get_hand());

    std::sort(all_cards.begin(), all_cards.end(), Card::greater);

    // count same suits for flush-dro
    int suit_counter[4] = {0};
    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i) {
        if (++suit_counter[(*i)->get_suit()] == 4) {
            is_flush_dro = true;
            outs += 9;
            break;
        }
    }

    // check two-side straight-dro
    int last_face = -1, count = 0;
    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i)
    {
        // ignore cards of same face
        if (last_face == (*i)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*i)->get_face()) {
            count = 1;
        } else {
            if (++count == 4)
            {
                is_straight_dro = true;
                outs += 8;
                break;
            }
        }
        last_face = (*i)->get_face();
    }
    if (is_straight_dro && last_face == Card::JACK) {
        outs -= 4;
        is_straight_dro = false;
        is_gutshot = true;
    }
    // check "wheel"
    if (all_cards.front()->get_face() == Card::ACE && count == 3 &&
        last_face == Card::TWO) {
        is_gutshot = true;
    }

    // check gutshot
    last_face = -1, count = 0;
    bool hole = false;
    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i)
    {
        // ignore cards of same face
        if (last_face == (*i)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*i)->get_face()) {
            // check hole
            if (!hole && last_face - 2 == (*i)->get_face()) {
                count++;
                hole = true;
            } else {
                count = 1;
            }
        } else {
            if (++count == 5)
            {
                is_gutshot = true;
                outs += 4;
                break;
            }
        }
        last_face = (*i)->get_face();
    }
    // check gutshot in "wheel"
    if (all_cards.front()->get_face() == Card::ACE &&
        last_face == Card::TWO && hole && count == 4) {
        is_gutshot = true;
        outs += 4;
    }

    // remove 2 cards that we have counted twice
    if (is_flush_dro && is_straight_dro) {
        outs -= 2;
    }
    // remove card that we have counted twice
    if (is_flush_dro && is_gutshot) {
        outs -= 1;
    }

    // unlucky
    if (strength->get_combination() == Hand_strength::HIGH_CARD &&
        is_flush_dro && is_straight_dro) {
        return outs;
    }

    // pair => three of a kind
    if (strength->get_combination() == Hand_strength::PAIR) {
        outs += 2;
    }

    // two pairs => three of a kind
    if (strength->get_combination() == Hand_strength::TWO_PAIRS) {
        outs += 4;
    }

    // three of a kind => four of a kind
    if (strength->get_combination() == Hand_strength::TREE_OF_A_KIND) {
        outs += 1;
    }

    // three of a kind => full house
    if (strength->get_combination() == Hand_strength::TREE_OF_A_KIND) {
        if (all_cards.size() == 5) {
            outs += 6;
        } else {
            outs += 9;
        }
    }

    return outs;
}

bool ComputerPlayer::check_pot_odds(chips_t &bet)
{
    int combination_odds;
    if (outs <= 3) {
        combination_odds = outs * 2;
    } else if (outs >= 12) {
        combination_odds = outs * 2 + 2;
    } else {
        combination_odds = outs * 2 + 1;
    }

    if (bet * 100.0 / (bet + *pot) <= combination_odds) {
        return true;
    }

    return false;
}
