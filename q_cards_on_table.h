#ifndef QCARDSONTABLE_H
#define QCARDSONTABLE_H

#include <QObject>
#include <QLabel>
#include <QVector>
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
    virtual round_t set_preflop();
    virtual round_t set_flop(DeckOfCards *deck);
    virtual round_t set_turn(DeckOfCards *deck);
    virtual round_t set_river(DeckOfCards *deck);
signals:
    void deal_cards_on_table(QVector<QLabel*> &cards_images);
    void turn_cards_on_table(vector<const Card*> &cards,
                               QVector<QLabel*> &cards_images);
    void deal_card_on_table(QLabel *card_image);
    void turn_card_on_table(const Card *card, QLabel *card_image);
    void clear_cards_on_table(QVector<QLabel*> &cards_images);

public slots:

private:
    QVector<QLabel*> cards_images;
};

#endif // QCARDSONTABLE_H
