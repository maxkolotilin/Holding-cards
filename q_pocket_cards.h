#ifndef QPOCKETCARDS_H
#define QPOCKETCARDS_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include "src/pocket_cards.h"
#include "keepers.h"

class QPocketCards : public QObject, Pocket_cards
{
    Q_OBJECT
public:
    explicit QPocketCards(QLabel *card_1, QLabel *card_2,
                          ImageKeeper *ik, QObject *parent = 0);
    ~QPocketCards();

    void set_card(const Card *c);
    void clear();
    void show_hand();

private:
    QVector<QLabel *> hand_images;

signals:
    void set_card_back(QLabel *card_image);
    void set_blank_cards(QVector<QLabel *> &hand_images);
    void set_cards_faces(vector<const Card*> &hand,
                         QVector<QLabel *> &hand_images);

public slots:
};

#endif // QPOCKETCARDS_H
