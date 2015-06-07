/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for q_pocket_cards.h
 */

#include "q_pocket_cards.h"

QPocketCards::QPocketCards(QLabel *card_1, QLabel *card_2, ImageKeeper *ik,
                           QObject *parent) : PocketCards(parent)
{
    hand_images.reserve(POCKET_SIZE);
    hand_images.push_back(card_1);
    hand_images.push_back(card_2);

    connect(this, SIGNAL(set_blank_cards(QVector<QLabel*>)),
            ik, SLOT(clear_cards(QVector<QLabel*>)));
    connect(this, SIGNAL(flip_cards(vector<const Card*>&, QVector<QLabel*>)),
            ik, SLOT(flip_cards(vector<const Card*>&, QVector<QLabel*>)));
    connect(this, SIGNAL(set_card_back(QLabel*)),
            ik, SLOT(set_back(QLabel*)));
}

QPocketCards::~QPocketCards()
{
    disconnect();
}

void QPocketCards::set_card(const Card *card)
{
    PocketCards::set_card(card);

    emit set_card_back(hand_images.back());
    QApplication::processEvents();
}

void QPocketCards::reset_pocket_cards()
{
    PocketCards::reset_pocket_cards();

    emit set_blank_cards(hand_images);
    QApplication::processEvents();
}

void QPocketCards::show_hand()
{
    emit flip_cards(pocket_cards, hand_images);
    QApplication::processEvents();
}

