/*
 * Created by MaximKa on 12.04.2015
 *
 * License: none
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for Evaluator.h
 *
 */

#include "evaluator.h"
#include "src/card.h"
#include <algorithm>

using std::vector;

const string Hand_strength::combinations[] = { "High card", "Pair",
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

Hand_strength::Hand_strength()
{
    comb_cards.reserve(5);
    kicker.reserve(5);
}

Hand_strength::~Hand_strength() {}

bool Hand_strength::operator < (const Hand_strength &hs) const
{
    if (get_combination() < hs.get_combination()) {
        return true;
    } else if (get_combination() > hs.get_combination()) {
        return false;
    }

    for (unsigned i = 0; i < comb_cards.size(); ++i) {
        if (comb_cards[i]->get_face() < hs.comb_cards[i]->get_face()) {
            return true;
        } else if (comb_cards[i]->get_face() > hs.comb_cards[i]->get_face()) {
            return false;
        }
    }

    for (unsigned i= 0; i < kicker.size(); ++i) {
        if (kicker[i]->get_face() < hs.kicker[i]->get_face()) {
            return true;
        } else if (kicker[i]->get_face() > hs.kicker[i]->get_face()) {
            return false;
        }
    }

    return false;
}

bool Hand_strength::operator > (const Hand_strength &hs) const
{
    if (get_combination() > hs.get_combination()) {
        return true;
    } else if (get_combination() < hs.get_combination()) {
        return false;
    }

    for (unsigned i = 0; i < comb_cards.size(); ++i) {
        if (comb_cards[i]->get_face() > hs.comb_cards[i]->get_face()) {
            return true;
        } else if (comb_cards[i]->get_face() < hs.comb_cards[i]->get_face()) {
            return false;
        }
    }

    for (unsigned i= 0; i < kicker.size(); ++i) {
        if (kicker[i]->get_face() > hs.kicker[i]->get_face()) {
            return true;
        } else if (kicker[i]->get_face() < hs.kicker[i]->get_face()) {
            return false;
        }
    }

    return false;
}

bool Hand_strength::operator == (const Hand_strength &hs) const
{
    if (get_combination() != hs.get_combination()) {
        return false;
    }

    for (unsigned i = 0; i < comb_cards.size(); ++i) {
        if (comb_cards[i]->get_face() != hs.comb_cards[i]->get_face()) {
            return false;
        }
    }

    for (unsigned i = 0; i < kicker.size(); ++i) {
        if (kicker[i]->get_face() != hs.kicker[i]->get_face()) {
            return false;
        }
    }

    return true;
}

//========================== Evaluator =======================================

Evaluator::Evaluator(Cards_on_table *cards)
{
    community_cards = cards;
    all_cards.reserve(7);
}

Evaluator::~Evaluator() {}

void Evaluator::get_strength(Pocket_cards *pocket, Cards_on_table *community,
                            Hand_strength *strength)
{
    all_cards.clear();
    copyToAllCards(pocket->get_hand());
    copyToAllCards(community->get_table_cards());

    get_strength(strength);
}

void Evaluator::get_strength(Hand_strength *strength)
{
    // sort cards descending
    std::sort(all_cards.begin(), all_cards.end(), Card::greater);

    // clear combination cards and kicker
    strength->clear_comb_cards();
    strength->clear_kicker();

    // test for all combinations
    bool is_flush;
    if ((is_flush = isFlush(strength)) &&
        isStraight(strength, strength->comb_cards.front()->get_suit())) {
        strength->combination = Hand_strength::STRAIGHT_FLUSH;
        // check royal flush
        if (strength->comb_cards.front()->get_face() == Card::ACE) {
            strength->combination = Hand_strength::ROYAL_FLUSH;
        }
    } else if (isXOfAKind(4, strength)) {
        strength->combination = Hand_strength::FOUR_OF_A_KIND;
    } else if (isFullHouse(strength)) {
        strength->combination = Hand_strength::FULL_HOUSE;
    } else if (is_flush) {
        strength->combination = Hand_strength::FLUSH;
    } else if (isStraight(strength)) {
        strength->combination = Hand_strength:: STRAIGHT;
    } else if (isXOfAKind(3, strength)) {
        strength->combination = Hand_strength::TREE_OF_A_KIND;
    } else if (isTwoPair(strength)) {
        strength->combination = Hand_strength::TWO_PAIRS;
    } else if (isXOfAKind(2, strength)) {
        strength->combination = Hand_strength::PAIR;
    } else {
        strength->combination = Hand_strength::HIGH_CARD;

        strength->clear_comb_cards();
        strength->comb_cards.push_back(all_cards.front());
        strength->clear_kicker();
        for (iterator_t i = all_cards.begin() + 1;
             i != all_cards.end() && strength->kicker.size() < 4; ++i) {
            strength->kicker.push_back(*i);
        }
    }
}

bool Evaluator::isTwoPair(Hand_strength *strength)
{
    bool is_twopair = false;

    // contains first Pair
    if (isXOfAKind(2, strength))
    {
        const Card *fp = strength->comb_cards.front();
        // and contains a second Pair (other than first pair face)
        // use previous rank for "exclude"
        if (isXOfAKind(2, strength))
        {
            const Card *sp = strength->comb_cards.front();

            strength->clear_comb_cards();
            strength->comb_cards.push_back(fp);
            strength->comb_cards.push_back(sp);

            // copy remaining one kicker
            strength->kicker.clear();
            for (iterator_t i = all_cards.begin();
                 i != all_cards.end(); ++i) {
                if ((*i)->get_face() != fp->get_face() &&
                    (*i)->get_face() != sp->get_face()) {
                    strength->kicker.push_back(*i);
                    break;
                }
            }
            is_twopair = true;
        }
    }

    return is_twopair;
}

bool Evaluator::isStraight(Hand_strength *strength, const int suit)
//default suit = -1
{
    bool is_straight = false;
    int last_face = -1, count = 0;
    const Card *high;

    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i)
    {
        // ignore wrong suit when testing for Straight Flush
        if (suit != -1 && (*i)->get_suit() != suit) {
            continue;
        }
        // ignore cards of same face
        if (last_face == (*i)->get_face()) {
            continue;
        }
        if (last_face - 1 != (*i)->get_face()) {
            count = 1;
            high = *i;
        } else {
            if (++count == 5)
            {
                is_straight = true;
                break;
            }
        }

        last_face = (*i)->get_face();
    }

    // check "wheel" (A2345)
    if (count == 4 && last_face == Card::TWO &&
        all_cards.front()->get_face() == Card::ACE) {
        if (suit == -1) {
            is_straight = true;
        } else {
            // correct test for Straight Flush "wheel"
            for (iterator_t i = all_cards.begin();
                 (*i)->get_face() == Card::ACE; ++i) {
                if ((*i)->get_suit() == suit) {
                    is_straight = true;
                    break;
                }
            }
        }
    }

    if (is_straight)
    {
        strength->clear_comb_cards();
        strength->comb_cards.push_back(high);
        // TODO: add full hand
    }

    return is_straight;
}

bool Evaluator::isFlush(Hand_strength *strength)
{
    bool is_flush = false;
    Card::Suit_t flush_suit;
    int suit_counter[4] = {0};

    // count same suits
    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i) {
        if (++suit_counter[(*i)->get_suit()] == 5) {
            flush_suit = (*i)->get_suit();
            is_flush = true;
            break;
        }
    }

    if (is_flush)
    {
        // copy all cards with flush suit as rank; max 5 cards
        strength->clear_comb_cards();
        int count = 0;
        for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i) {
            if ((*i)->get_suit() == flush_suit) {
                strength->comb_cards.push_back(*i);
                if (++count = 5) {
                    break;
                }
            }
        }
    }

    return is_flush;
}

bool Evaluator::isXOfAKind(const int num, Hand_strength *strength)
{
    bool is_xofakind = false;
    int face = -1;
    const Card *high;
    int counter = 0;

    // count face of cards, break on n of a kind
    for (iterator_t i = all_cards.begin(); i != all_cards.end(); ++i) {
        // ignore face which might be in comb-vector at first index
        if (strength->comb_cards.size() &&
            strength->comb_cards.front()->get_face() == (*i)->get_face()) {
            continue;
        }

        if ((*i)->get_face() != face) {
            face = (*i)->get_face();
            counter = 1;
            high = *i;
        } else {
            if (++counter == num) {
                is_xofakind = true;
                break;
            }
        }
    }

    // clear combination and kicker in any case
    strength->clear_comb_cards();
    strength->clear_kicker();

    if (is_xofakind)
    {
        // comb card is highest first card of XOfAKind
        strength->comb_cards.push_back(high);

        // copy the kicker; max (5-n) card
        int c = 0;
        for (iterator_t i = all_cards.begin();
             i != all_cards.end(); ++i) {
            if ((*i)->get_face() != face) {
                strength->comb_cards.push_back(*i);
                if (++c == 5 - num) {
                    break;
                }
            }
        }
    }

    return is_xofakind;
}

bool Evaluator::isFullHouse(Hand_strength *strength)
{
    bool is_fullhouse = false;

    // strength contains Three of a Kind
    if (isXOfAKind(3, strength))
    {
        const Card *three = strength->comb_cards.front();

        // and contains a Pair (other than the Three of a Kind-card)
        // use previous comb card as "exclude"
        if (isXOfAKind(2, strength))
        {
            const Card *deuce = strength->comb_cards.front();

            strength->clear_comb_cards();
            strength->comb_cards.push_back(three);
            strength->comb_cards.push_back(deuce);

            is_fullhouse = true;
        }
    }

    return is_fullhouse;
}

void Evaluator::get_win_list(vector<Hand_strength> &hands,
                             vector<vector<Hand_strength>> &winlist)
//TODO
{
    winlist.clear();
    winlist.push_back(hands);

    int index = 0;
    do
    {
        vector<Hand_strength> &tw = winlist[index];
        vector<Hand_strength> tmp;

        sort(tw.begin(), tw.end(), std::greater<Hand_strength>());

        for (int i = tw.size() - 1; i > 0; --i)
        {
            if (tw[i] < tw[0])
            {
                tmp.push_back(tw[i]);
                tw.pop_back();
            }
        }

        if (!tmp.size())
            break;

        winlist.push_back(tmp);
        index++;

    } while (true);
}
