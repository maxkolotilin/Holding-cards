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
    last_action = Player::NONE;
    sitout = false;
    hand = new Pocket_cards();
}

/*virtual*/ Player::~Player()
{
    delete hand;
}

Player::chips_t Player::blind(blind_t type)
{
    if (type == BIG_BLIND) {
        stack -= min_bet;
        return min_bet;
    } else {
        stack -= min_bet / 2;
        return min_bet / 2;
    }
}

Player::chips_t Player::stake(action_t action)
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

ComputerPlayer::ComputerPlayer(int id) : Player(id)
{

}

ComputerPlayer::~ComputerPlayer()
{

}

bool ComputerPlayer::check_top_10_hands()
{
    // TT, JJ, QQ, KK, AA
    if (*(hand->pocket_cards.front()) == *(hand->pocket_cards.back()) &&
        hand->pocket_cards.front()->get_face() > Card::NINE) {
        return true;
    }
    // AKs, AQs, KQs, AJs,
    if (hand->pocket_cards.front()->get_suit() ==
        hand->pocket_cards.back()->get_suit()) {
        switch (hand->pocket_cards.front()->get_face() +
                hand->pocket_cards.back()->get_face())
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
    if (hand->pocket_cards.front()->get_face() +
        hand->pocket_cards.back()->get_face() ==
        Card::ACE + Card::KING) {
        return true;
    }

    return false;
}

bool ComputerPlayer::check_top_21_hands()
{
    // 88, 99
    if (*(hand->pocket_cards.front()) == *(hand->pocket_cards.back()) &&
        hand->pocket_cards.front()->get_face() > Card::SEVEN) {
        return true;
    }
    // ATs, KJs, QJs, KTs, QTs, A9s
    if (hand->pocket_cards.front()->get_suit() ==
        hand->pocket_cards.back()->get_suit()) {
        switch (hand->pocket_cards.front()->get_face() +
                hand->pocket_cards.back()->get_face())
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
    if (hand->pocket_cards.front()->get_face() +
        hand->pocket_cards.back()->get_face() ==
        Card::ACE + Card::QUEEN) {
        return true;
    }
    if (hand->pocket_cards.front()->get_face() +
        hand->pocket_cards.back()->get_face() ==
        Card::ACE + Card::JACK) {
        return true;
    }

    return false;
}
