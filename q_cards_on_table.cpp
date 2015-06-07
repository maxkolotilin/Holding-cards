/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for q_cards_on_table.h
 */

#include "q_cards_on_table.h"

QCardsOnTable::QCardsOnTable(QLabel *flop_1, QLabel *flop_2, QLabel *flop_3,
                             QLabel *turn, QLabel *river, ImageKeeper *ik,
                             QObject *parent) : CardsOnTable(parent)
{
    cards_images.reserve(CARDS_ON_TABLE_SIZE);
    cards_images.push_back(flop_1);
    cards_images.push_back(flop_2);
    cards_images.push_back(flop_3);
    cards_images.push_back(turn);
    cards_images.push_back(river);

    connect(this, SIGNAL(clear_cards_on_table(QVector<QLabel*>)),
            ik, SLOT(clear_cards(QVector<QLabel*>)));
    connect(this, SIGNAL(deal_cards_on_table(QVector<QLabel*>)),
            ik, SLOT(set_backs(QVector<QLabel*>)));
    connect(this, SIGNAL(deal_card_on_table(QLabel*)),
            ik, SLOT(set_back(QLabel*)));
    connect(this, SIGNAL(flip_cards_on_table(vector<const Card*>&, QVector<QLabel*>)),
            ik, SLOT(flip_cards(vector<const Card*>&, QVector<QLabel*>)));
    connect(this, SIGNAL(flip_card_on_table(const Card*, QLabel*)),
            ik, SLOT(flip_card(const Card*, QLabel*)));
}

QCardsOnTable::~QCardsOnTable()
{
    disconnect();
}

QCardsOnTable::round_t QCardsOnTable::reset_cards_on_table()
{
    emit clear_cards_on_table(cards_images);
    QApplication::processEvents();

    return CardsOnTable::reset_cards_on_table();
}

QCardsOnTable::round_t QCardsOnTable::set_flop(DeckOfCards *deck)
{
    round_t round = CardsOnTable::set_flop(deck);

    QVector<QLabel *> flop_cards;
    for (int i = 0; i < CARDS_ON_FLOP; ++i) {
        flop_cards.push_back(cards_images[i]);
    }
    emit deal_cards_on_table(flop_cards);
    emit flip_cards_on_table(cards_on_table, flop_cards);
    QApplication::processEvents();

    return round;
}

QCardsOnTable::round_t QCardsOnTable::set_turn(DeckOfCards *deck)
{
    round_t round = CardsOnTable::set_turn(deck);

    emit deal_card_on_table(cards_images[CARDS_ON_TURN - 1]);
    emit flip_card_on_table(cards_on_table[CARDS_ON_TURN - 1],
                            cards_images[CARDS_ON_TURN - 1]);
    QApplication::processEvents();

    return round;
}

QCardsOnTable::round_t QCardsOnTable::set_river(DeckOfCards *deck)
{
    round_t round = CardsOnTable::set_river(deck);

    emit deal_card_on_table(cards_images[CARDS_ON_RIVER - 1]);
    emit flip_card_on_table(cards_on_table[CARDS_ON_RIVER - 1],
                            cards_images[CARDS_ON_RIVER - 1]);
    QApplication::processEvents();

    return round;
}

