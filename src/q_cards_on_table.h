/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class inherited from CardsOnTable
 * Add interaction with GUI
 */

#ifndef QCARDSONTABLE_H
#define QCARDSONTABLE_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include <QApplication>
#include "src/cards_on_table.h"
#include "keepers.h"

class QCardsOnTable : public CardsOnTable
{
    Q_OBJECT
public:
    explicit QCardsOnTable(QLabel *flop_1, QLabel *flop_2, QLabel *flop_3,
                           QLabel *turn, QLabel *river, ImageKeeper *ik,
                           QObject *parent = 0);
    ~QCardsOnTable();

    virtual round_t set_flop(DeckOfCards *deck);
    virtual round_t set_turn(DeckOfCards *deck);
    virtual round_t set_river(DeckOfCards *deck);
    virtual round_t reset_cards_on_table();

signals:
    // deal cards backs up
    void deal_cards_on_table(QVector<QLabel*> cards_images);
    void deal_card_on_table(QLabel *card_image);

    void flip_cards_on_table(vector<const Card*> &cards,
                             QVector<QLabel*> cards_images);
    void flip_card_on_table(const Card *card, QLabel *card_image);

    void clear_cards_on_table(QVector<QLabel*> cards_images);

public slots:

private:
    QVector<QLabel*> cards_images;
};

#endif // QCARDSONTABLE_H
