#include "q_cards_on_table.h"
#include <QApplication>

QCardsOnTable::QCardsOnTable(QLabel *flop_1, QLabel *flop_2, QLabel *flop_3,
                             QLabel *turn, QLabel *river, ImageKeeper *ik,
                             QObject *parent) : Cards_on_table()
{
    cards_images.reserve(5);
    cards_images.push_back(flop_1);
    cards_images.push_back(flop_2);
    cards_images.push_back(flop_3);
    cards_images.push_back(turn);
    cards_images.push_back(river);

    connect(this, SIGNAL(clear_cards_on_table(QVector<QLabel*>&)),
            ik, SLOT(clear_cards(QVector<QLabel*>&)));
    connect(this,
            SIGNAL(update_cards_on_table(vector<const Card*>&,QVector<QLabel*>&)),
            ik, SLOT(set_faces(vector<const Card*>&,QVector<QLabel*>&)));
    connect(this, SIGNAL(update_card_on_table(const Card*,QLabel*)),
            ik, SLOT(set_face(const Card*,QLabel*)));
}

QCardsOnTable::~QCardsOnTable()
{
    disconnect();
}

QCardsOnTable::Round_t QCardsOnTable::set_preflop()
{
    Round_t round = Cards_on_table::set_preflop();

    emit clear_cards_on_table(cards_images);
    QApplication::processEvents();
    return round;
}

QCardsOnTable::Round_t QCardsOnTable::set_flop(Deck_of_cards *deck)
{
    Round_t round = Cards_on_table::set_flop(deck);

    QVector<QLabel *> flop_cards;
    for (int i = 0; i < 3; ++i) {
        flop_cards.push_back(cards_images[i]);
    }
    emit update_cards_on_table(cards_on_table, flop_cards);
    QApplication::processEvents();
    return round;
}

QCardsOnTable::Round_t QCardsOnTable::set_turn(Deck_of_cards *deck)
{
    Round_t round = Cards_on_table::set_turn(deck);

    emit update_card_on_table(cards_on_table[3], cards_images[3]);
    QApplication::processEvents();
    return round;
}

QCardsOnTable::Round_t QCardsOnTable::set_river(Deck_of_cards *deck)
{
    Round_t round = Cards_on_table::set_river(deck);

    emit update_card_on_table(cards_on_table[3], cards_images[3]);
    QApplication::processEvents();
    return round;
}

