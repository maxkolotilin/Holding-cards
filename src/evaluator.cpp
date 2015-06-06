/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for Evaluator.h
 *
 */

#include "evaluator.h"
#include <algorithm>

const string HandStrength::combinations[] = { "High card", "Pair",
                            "Two pairs", "Three of a kind","Straight",
                            "Flush", "Full house", "Four of a kind",
                            "Straight flush", "Royal flush" };

/*
    Ranking          Rank-card(s)           Kicker-card(s)
    ------------------------------------------------------
    HighCard         Top card               Remaining 4
    OnePair          Pair card              Remaining 3
    TwoPair          1st & 2nd Pair card    Remaining 1
    ThreeOfAKind     Trips card             Remaining 2
    Straight         Top card               -
    Flush            Flush cards            -
    FullHouse        Trips & Pair card      -
    FourOfAKind      FourOfAKind card       Remaining 1
    StraightFlush    Top card               -
    FlashRoyal       -                      -
*/

HandStrength::HandStrength()
{
    combination_cards.reserve(CardsOnTable::CARDS_ON_TABLE_SIZE);
    kicker_cards.reserve(CardsOnTable::CARDS_ON_TABLE_SIZE);
}

HandStrength::~HandStrength()
{

}

bool HandStrength::operator < (const HandStrength &hs) const
{
    if (get_combination() < hs.get_combination()) {
        return true;
    } else if (get_combination() > hs.get_combination()) {
        return false;
    }
    // compare combination cards
    for (size_t i = 0; i < combination_cards.size(); ++i) {
        if (combination_cards[i]->get_face() <
            hs.combination_cards[i]->get_face()) {
            return true;
        } else if (combination_cards[i]->get_face() >
                   hs.combination_cards[i]->get_face()) {
            return false;
        }
    }
    // compare kicker cards
    for (size_t i= 0; i < kicker_cards.size(); ++i) {
        if (kicker_cards[i]->get_face() < hs.kicker_cards[i]->get_face()) {
            return true;
        } else if (kicker_cards[i]->get_face() > hs.kicker_cards[i]->get_face()) {
            return false;
        }
    }

    return false;
}

bool HandStrength::operator > (const HandStrength &hs) const
{
//    if (get_combination() > hs.get_combination()) {
//        return true;
//    } else if (get_combination() < hs.get_combination()) {
//        return false;
//    }

//    for (int i = 0; i < combination_cards.size(); ++i) {
//        if (combination_cards[i]->get_face() > hs.combination_cards[i]->get_face()) {
//            return true;
//        } else if (combination_cards[i]->get_face() < hs.combination_cards[i]->get_face()) {
//            return false;
//        }
//    }

//    for (int i= 0; i < kicker_cards.size(); ++i) {
//        if (kicker_cards[i]->get_face() > hs.kicker_cards[i]->get_face()) {
//            return true;
//        } else if (kicker_cards[i]->get_face() < hs.kicker_cards[i]->get_face()) {
//            return false;
//        }
//    }

//    return false;

    return hs < *this;
}

bool HandStrength::operator == (const HandStrength &hs) const
{
    if (get_combination() != hs.get_combination()) {
        return false;
    }
    // compare combination cards
    for (unsigned i = 0; i < combination_cards.size(); ++i) {
        if (combination_cards[i]->get_face() != hs.combination_cards[i]->get_face()) {
            return false;
        }
    }
    // compare kicker cards
    for (unsigned i = 0; i < kicker_cards.size(); ++i) {
        if (kicker_cards[i]->get_face() != hs.kicker_cards[i]->get_face()) {
            return false;
        }
    }

    return true;
}

void HandStrength::reset_hand_strength()
{
    clear_combination_cards();
    clear_kicker_cards();
    combination = NONE;
}

//========================== Evaluator =======================================

Evaluator::Evaluator(const CardsOnTable *cards)
{
    community_cards = cards;
    all_cards.reserve(CardsOnTable::CARDS_ON_TABLE_SIZE +
                      PocketCards::POCKET_SIZE);   // 7
}

Evaluator::~Evaluator()
{

}

void Evaluator::get_strength(PocketCards *pocket, HandStrength *strength)
{
    all_cards.clear();
    copy_to_all_cards(pocket->get_hand());
    copy_to_all_cards(community_cards->get_table_cards());

    get_strength(strength);
}

void Evaluator::get_strength(Player *player)
{
    get_strength(strength->get_hand(), strength->get_strength());
}

void Evaluator::get_strength(HandStrength *strength)
{
    // sort cards descending
    std::sort(all_cards.begin(), all_cards.end(), Card::greater);

    // clear combination cards and kicker_cards
    strength->clear_combination_cards();
    strength->clear_kicker_cards();

    // test for all combinations
    bool isFlush;
    if ((isFlush = is_flush(strength)) &&
        is_straight(strength,
                    strength->get_combination_cards()->front()->get_suit())) {
        strength->set_combination(HandStrength::STRAIGHT_FLUSH);
        // check royal flush
        if (strength->get_combination_cards()->front()->get_face() == Card::ACE) {
            strength->set_combination(HandStrength::ROYAL_FLUSH);
        }
    } else if (is_X_of_a_kind(4, strength)) {
        strength->set_combination(HandStrength::FOUR_OF_A_KIND);
    } else if (is_full_house(strength)) {
        strength->set_combination(HandStrength::FULL_HOUSE);
    } else if (isFlush) {
        strength->set_combination(HandStrength::FLUSH);
    } else if (is_straight(strength)) {
        strength->set_combination(HandStrength:: STRAIGHT);
    } else if (is_X_of_a_kind(3, strength)) {
        strength->set_combination(HandStrength::TREE_OF_A_KIND);
    } else if (is_two_pairs(strength)) {
        strength->set_combination(HandStrength::TWO_PAIRS);
    } else if (is_X_of_a_kind(2, strength)) {
        strength->set_combination(HandStrength::PAIR);
    } else {
        strength->set_combination(HandStrength::HIGH_CARD);

        strength->clear_combination_cards();
        strength->add_to_combination_cards(all_cards.front());
        strength->clear_kicker_cards();
        for (card_it card = all_cards.begin() + 1;
             card != all_cards.end() &&
             strength->get_kicker_cards()->size() < 4; ++card) {
            strength->add_to_kicker_cards(*card);
        }
    }
}

bool Evaluator::is_two_pairs(HandStrength *strength)
{
    bool is_twopairs = false;

    // contains first Pair
    if (is_X_of_a_kind(2, strength)) {
        const Card *fp = strength->get_combination_cards()->front();
        // and contains a second Pair (other than first pair face)
        // use previous rank for "exclude"
        if (is_X_of_a_kind(2, strength)) {
            const Card *sp = strength->get_combination_cards()->front();

            strength->clear_combination_cards();
            strength->add_to_combination_cards(fp);
            strength->add_to_combination_cards(sp);

            // copy remaining one kicker card
            strength->clear_kicker_cards();
            for (card_it card = all_cards.begin();
                 card != all_cards.end(); ++card) {
                if ((*card)->get_face() != fp->get_face() &&
                    (*card)->get_face() != sp->get_face()) {
                    strength->add_to_kicker_cards(*card);
                    break;
                }
            }
            is_twopairs = true;
        }
    }

    return is_twopairs;
}

bool Evaluator::is_straight(HandStrength *strength, const int suit /* = -1 */)
{
    bool is_straight = false;
    int last_face = -1, counter = 0;
    const Card *high_card;

    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
        // ignore wrong suit when testing for Straight Flush
        if (suit != -1 && (*card)->get_suit() != suit) {
            continue;
        }
        // ignore cards of same face
        if (last_face == (*card)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*card)->get_face()) {
            counter = 1;
            high_card = *card;
        } else {
            if (++counter == 5) {
                is_straight = true;
                break;
            }
        }

        last_face = (*card)->get_face();
    }

    // check "wheel" (A2345)
    if (counter == 4 && last_face == Card::TWO &&
        all_cards.front()->get_face() == Card::ACE) {
        if (suit == -1) {
            is_straight = true;
        } else {
            // correct test for Straight Flush "wheel"
            for (card_it card = all_cards.begin();
                 (*card)->get_face() == Card::ACE; ++card) {
                if ((*card)->get_suit() == suit) {
                    is_straight = true;
                    break;
                }
            }
        }
    }

    if (is_straight) {
        strength->clear_combination_cards();
        strength->add_to_combination_cards(high_card);
    }

    return is_straight;
}

bool Evaluator::is_flush(HandStrength *strength)
{
    bool is_flush = false;
    Card::suit_t flush_suit;
    int suit_counter[Card::NUMBER_OF_SUITS] = {0};

    // count same suits
    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
        if (++suit_counter[(*card)->get_suit()] == 5) {
            flush_suit = (*card)->get_suit();
            is_flush = true;
            break;
        }
    }

    if (is_flush)
    {
        // copy all cards with flush suit as rank; max 5 cards
        strength->clear_combination_cards();
        int counter = 0;
        for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
            if ((*card)->get_suit() == flush_suit) {
                strength->add_to_combination_cards(*card);
                if (++counter = 5) {
                    break;
                }
            }
        }
    }

    return is_flush;
}

bool Evaluator::is_X_of_a_kind(const int X, HandStrength *strength)
{
    bool is_xofakind = false;
    int face = -1;
    const Card *high_card;
    int counter = 0;

    // count face of cards, break on X of a kind
    for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
        // ignore face which might be in comb-vector at first index
        if (strength->get_combination_cards()->size() &&
            strength->get_combination_cards()->front()->get_face() ==
            (*card)->get_face()) {
            continue;
        }

        if ((*card)->get_face() != face) {
            face = (*card)->get_face();
            counter = 1;
            high_card = *card;
        } else {
            if (++counter == X) {
                is_xofakind = true;
                break;
            }
        }
    }

    // clear combination and kicker_cards in any case
    strength->clear_combination_cards();
    strength->clear_kicker_cards();

    if (is_xofakind)
    {
        // comb card is highest first card of XOfAKind
        strength->add_to_combination_cards(high_card);

        // copy the kicker_cards; max (5-n) card
        int counter = 0;
        for (card_it card = all_cards.begin(); card != all_cards.end(); ++card) {
            if ((*card)->get_face() != face) {
                strength->add_to_kicker_cards(*card);
                if (++counter == 5 - X) {
                    break;
                }
            }
        }
    }

    return is_xofakind;
}

bool Evaluator::is_full_house(HandStrength *strength)
{
    bool is_fullhouse = false;

    // strength contains Three of a Kind
    if (is_X_of_a_kind(3, strength))
    {
        const Card *three = strength->get_combination_cards()->front();

        // and contains a Pair (other than the Three of a Kind-card)
        // use previous comb card as "exclude"
        if (is_X_of_a_kind(2, strength))
        {
            const Card *deuce = strength->get_combination_cards()->front();

            strength->clear_combination_cards();
            strength->add_to_combination_cards(three);
            strength->add_to_combination_cards(deuce);

            is_fullhouse = true;
        }
    }

    return is_fullhouse;
}

/////////////////////////////////////////////////////////////////////
void Evaluator::get_win_list(list<Player*> &players,
                             vector<vector<Player*>> &winlist)
// For example, winlist may be something like that
// [
//      [pl_1(5, 6, 7, 8, 9), pl_2(5, 6, 7, 8, 9)],
//      [pl_3(5, 5)],
//      [pl_4(high_card card)]
// ]
// In this case pl_1 and pl_2 won and will divide pot in two
{
    vector<Player*> players_on_showdown;
    for (player_it player = players.begin(); player != players.end();
         ++player) {
        if (((*player)->get_last_action().action != Player::FOLD) !=
            ((*player)->get_last_action().action != Player::NONE)) {
            players_on_showdown.push_back(*player);
        }
    }

    winlist.clear();
    winlist.push_back(players_on_showdown);

    int index = 0;
    while (true) {
        vector<Player*> &current_list = winlist[index];
        vector<Player*> weaker_players;

        // sort players descending
        std::sort(current_list.begin(), current_list.end(),
                  Player::greater);

        for (int i = current_list.size(); i > 1; --i) {
            if (*(current_list[i]) < *(current_list[0])) {
                weaker_players.push_back(current_list[i]);
                current_list.pop_back();
            }
        }

        if (weaker_players.size() == 0) {
            // there is no more weaker players, winlist is completed
            break;
        }

        winlist.push_back(weaker_players);
        index++;
    }
}
