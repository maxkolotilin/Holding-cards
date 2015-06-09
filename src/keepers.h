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
#include <QSound>
#include <QPainter>
#include <QEventLoop>
#include <QPropertyAnimation>
#include <QApplication>
#include <exception>
#include "src/core/evaluator.h"

class SoundKeeper;

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
                         SoundKeeper *sk, QObject *parent = 0);
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

    SoundKeeper *sound_keeper;

signals:
    void deal_card(QLabel *card);

public slots:
    void set_backs(QVector<QLabel*> cards_images);
    void set_back(QLabel *card_image);

    void flip_cards(vector<const Card*> &cards, QVector<QLabel*> cards_images);
    void flip_card(const Card *card, QLabel *card_image);

    void clear_cards(QVector<QLabel*> cards_images);
    void deal_card_animation(QLabel *card);

    void set_dealer_puck(QLabel *puck);
    void set_blind_puck(QLabel *puck, Player::blind_t blind);
    void clear_puck(QLabel *puck);

    void set_winner_image(QLabel *message);
};

class SoundKeeper : public QObject
{
    Q_OBJECT
public:
    typedef enum { VAR_1 } choice_t;
    typedef enum { ALL_IN_SOUND, CALL_SOUND, CHECK_SOUND, RAISE_SOUND,
                   FOLD_SOUND, INCREASE_BET_SOUND, ACTIVATE_HUMAN_SOUND,
                   DEAL_CARD_SOUND } sounds_t;
    static const int NUMBER_OF_SOUNDS = 8;

    SoundKeeper(QObject *parent = 0);
    ~SoundKeeper();
private:
    const QString PATH = "res/sound/";

    QVector<QSound *> sounds;

public slots:
    void play_all_in_sound();
    void play_call_sound();
    void play_check_sound();
    void play_raise_sound();
    void play_fold_sound();
    void play_increase_bet_sound();
    void play_activate_human_sound();
    void play_deal_card_sound();

};

#endif // KEEPERS_H
