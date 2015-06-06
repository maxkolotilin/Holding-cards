#include "q_pocket_cards.h"
#include <QApplication>

QPocketCards::QPocketCards(QLabel *card_1, QLabel *card_2, ImageKeeper *ik,
                           QObject *parent)
    : PocketCards()
{
    hand_images.reserve(2);
    hand_images.push_back(card_1);
    hand_images.push_back(card_2);

    connect(this, SIGNAL(set_blank_cards(QVector<QLabel*>&)),
            ik, SLOT(clear_cards(QVector<QLabel*>&)));
    connect(this, SIGNAL(set_cards_faces(vector<const Card*>&,QVector<QLabel*>&)),
            ik, SLOT(set_faces(vector<const Card*>&,QVector<QLabel*>&)));
    connect(this, SIGNAL(set_card_back(QLabel*)),
            ik, SLOT(set_back(QLabel*))/*, Qt::DirectConnection*/);
}

QPocketCards::~QPocketCards()
{
    disconnect();
}

void QPocketCards::set_card(const Card *c)
{
    PocketCards::set_card(c);

    emit set_card_back(hand_images[cards_in_pocket - 1]);
    //QApplication::processEvents();
}

void QPocketCards::reset_pocket_cards()
{
    PocketCards::reset_pocket_cards();

    emit set_blank_cards(hand_images);
    QApplication::processEvents();
}

void QPocketCards::show_hand()
{
    emit set_cards_faces(pocket_cards, hand_images);
    QApplication::processEvents();
}

