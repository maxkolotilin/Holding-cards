/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class inherited from PocketCards
 * Add interaction with GUI
 */

#ifndef QPOCKETCARDS_H
#define QPOCKETCARDS_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include <QApplication>
#include "src/pocket_cards.h"
#include "keepers.h"

class QPocketCards : public PocketCards
{
    Q_OBJECT
public:
    explicit QPocketCards(QLabel *card_1, QLabel *card_2,
                          ImageKeeper *ik, QObject *parent = 0);
    ~QPocketCards();

    void set_card(const Card *card);
    void reset_pocket_cards();
    void show_hand();

private:
    QVector<QLabel *> hand_images;

signals:
    void set_card_back(QLabel *card_image);
    void set_blank_cards(QVector<QLabel *> hand_images);
    void flip_cards(vector<const Card*> &hand,
                         QVector<QLabel *> hand_images);

public slots:
};

#endif // QPOCKETCARDS_H
