/*
 * Created by Maxim Kolotilin on 01.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains classes that handle graphic and sound resources
 */

#ifndef KEEPERS_H
#define KEEPERS_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include <QEventLoop>
#include <QPropertyAnimation>
#include <QApplication>
#include <exception>
#include "src/evaluator.h"

class ImageKeeper : public QObject
{
    Q_OBJECT
public:
    // choice of deck, not implemented yet
    typedef enum { VAR_1, VAR_2 } choice_t;
    typedef enum { BACK, BLANK, TABLE, BAR_BACKGROUND, DEALER_PUCK, BIG_BLIND_PUCK,
                   SMALL_BLIND_PUCK, WINNER } picture_index_t;
    static const int NUMBER_OF_PICTURES = 8;
    static const int ANIMATION_DURATION = 333;    // in ms

    explicit ImageKeeper(QWidget *main_window, QLabel *animated_card,
                         QObject *parent = 0);
    ~ImageKeeper();

    void load_pictures(choice_t choice = VAR_1);   // throws exception
    void scale_cards(int width = DEFAULT_CARD_WIDTH,
                        int height = DEFAULT_CARD_HEIGHT);
    const QPixmap* get_card_image(const Card *card) const
    {
        return cards_img[card->get_face()][card->get_suit()];
    }
    const QPixmap* get_picture(picture_index_t index) const
    {
        return pictures[index];
    }

private:
    QVector<QVector<QPixmap *>> cards_img;  // [face][suit]
    QVector<QPixmap *> pictures;

    const QString PATH = "res/pic/";
    static const int DEFAULT_CARD_HEIGHT = 130;
    static const int DEFAULT_CARD_WIDTH = 90;

    QEventLoop *event_loop;
    QLabel *animated_card;

    QWidget *main_window;

signals:
    void deal_card(QLabel *card);

public slots:
//    void set_faces(vector<const Card*> &cards, QVector<QLabel*> cards_images);
//    void set_face(const Card *card, QLabel *card_image);

    void set_backs(QVector<QLabel*> cards_images);
    void set_back(QLabel *card_image);

    void flip_cards(vector<const Card*> &cards, QVector<QLabel*> cards_images);
    void flip_card(const Card *card, QLabel *card_image);

    void clear_cards(QVector<QLabel*> cards_images);
    void deal_card_animation(QLabel *card);

    void set_dealer_puck(QLabel *puck);
    void set_blind_puck(QLabel *puck, Player::blind_t blind);
    void clear_puck(QLabel *puck);
};

class SoundKeeper
{
public:
    enum choice_t { VAR_1 };

    SoundKeeper();
    ~SoundKeeper();
private:
    const QString PATH = "res/sound/";

};

#endif // KEEPERS_H
