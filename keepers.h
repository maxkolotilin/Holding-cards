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
    enum choice_t { VAR_1, VAR_2 };

    explicit ImageKeeper(QWidget *main_window, QLabel *animated_card,
                         bool scale = true, QObject *parent = 0);
    ~ImageKeeper();

    void load_pictures();

    void scale_cards(int width, int height);
    QPixmap* get_card_image(const Card *card);
    QPixmap* get_blank()
    {
        return blank;
    }
    QPixmap* get_card_back()
    {
        return back;
    }

private:
    QVector<QVector<QPixmap*>> cards_img;
    QPixmap *back;
    QPixmap *blank;
    QPixmap *table;
    QPixmap *bar_background;
    QPixmap *dealer_puck;
    QPixmap *big_blind_puck;
    QPixmap *small_blind_puck;


    const QString PATH = "res/pic/";
    const int DEFAULT_CARD_HEIGHT = 130;
    const int DEFAULT_CARD_WIDTH = 90;


    QEventLoop *event_loop;
    QLabel *animated_card;

    QWidget *main_window;

signals:
    void drop_card(QLabel *card);

public slots:
    void drop_card_animation(QLabel *card);
    void set_faces(vector<const Card*> &cards, QVector<QLabel*> cards_images);
    void set_face(const Card *card, QLabel *card_image);

    void clear_cards(QVector<QLabel*> cards_images);

    void set_backs(QVector<QLabel*> cards_images);
    void set_back(QLabel *card_image);

    void flip_cards(vector<const Card*> &cards, QVector<QLabel*> cards_images);
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
