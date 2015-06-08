/*
 * Created by Maxim Kolotilin on 01.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for keepers.h
 */
#include "keepers.h"

ImageKeeper::ImageKeeper(QWidget *main_window, QLabel *animated_card,
                         QObject *parent /* = 0 */)
    : QObject(parent)//, cards_img(QVector<QVector<QPixmap*>>(Card::NUMBER_OF_FACES,
                     //                    QVector<QPixmap*>(Card::NUMBER_OF_SUITS)))
{
    cards_img.reserve(Card::NUMBER_OF_FACES);
    for (int face = 0; face < Card::NUMBER_OF_FACES; ++face) {
        QVector<QPixmap *> suits;
        suits.reserve(Card::NUMBER_OF_SUITS);
        for (int suit = 0; suit < Card::NUMBER_OF_SUITS; ++suit) {
            suits.push_back(new QPixmap());
        }
        cards_img.push_back(suits);
    }

    pictures.reserve(NUMBER_OF_PICTURES);
    for (int i = 0; i < 8; ++i) {
        pictures.push_back(new QPixmap);
    }

    this->animated_card = animated_card;
    this->main_window = main_window;

    event_loop = new QEventLoop();
}

ImageKeeper::~ImageKeeper()
{
    disconnect();
    delete event_loop;
}

void ImageKeeper::load_pictures(choice_t choice)
{
    for (int face = 0; face < Card::NUMBER_OF_FACES; ++face) {
        for (int suit = 0; suit < Card::NUMBER_OF_SUITS; ++suit) {
            cards_img[face][suit]->load(PATH + QString::number(face) +
                                        QString::number(suit) + ".png");
            if (cards_img[face][suit]->isNull()) {
                throw new std::exception();
            }
        }
    }

    pictures[BACK]->load(PATH + "back212.png");
    pictures[BLANK]->load(PATH + "blank.png");
    pictures[TABLE]->load(PATH + "table.png");
    pictures[BAR_BACKGROUND]->load(PATH + "toolboxbg.png");
    pictures[DEALER_PUCK]->load(PATH + "dealerPuck.png");
    pictures[BIG_BLIND_PUCK]->load(PATH + "bigblindPuck.png");
    pictures[SMALL_BLIND_PUCK]->load(PATH + "smallblindPuck.png");
    pictures[WINNER]->load(PATH + "winner.png");

    foreach (QPixmap *pic, pictures) {
        if (pic->isNull()) {
            throw new std::exception();
        }
    }

    animated_card->setPixmap(*pictures[BACK]);
}

void ImageKeeper::scale_cards(int width, int height)
{
    foreach (QVector<QPixmap *> vector, cards_img) {
        foreach (QPixmap *pic, vector) {
            *pic = pic->scaled(width, height, Qt::IgnoreAspectRatio);
        }
    }
    *pictures[BACK] = pictures[BACK]->scaled(width, height, Qt::IgnoreAspectRatio);
    *pictures[BLANK] = pictures[BLANK]->scaled(width, height, Qt::IgnoreAspectRatio);
//    *pictures[TABLE] = pictures[TABLE]->scaled(main_window->size(),
//                                               Qt::IgnoreAspectRatio);

    animated_card->setPixmap(*pictures[BACK]);
}

// slots  ========================================================

//void ImageKeeper::set_faces(vector<const Card *> &cards,
//                            QVector<QLabel *> cards_images)
//{
//    // This slot inserts images according to cards in cards_images at the
//    // same order.

//    if (cards.size() == (unsigned)cards_images.size()) {
//        card_it card = cards.begin();
//        foreach (QLabel *element, cards_images) {
//            element->setPixmap(*get_card_image(*card));
//            ++card;
//        }
//    } else {
//        QMessageBox::warning(new QWidget(), "Error",
//                             "Error in slot of ImageKeeper: lenght mismatch.");
//    }
//}

//void ImageKeeper::set_face(const Card *card, QLabel *card_image)
//{
//    card_image->setPixmap(*get_card_image(card));
//}

void ImageKeeper::clear_cards(QVector<QLabel *> cards_images)
{
    foreach (QLabel *element, cards_images) {
        element->setPixmap(*pictures[BLANK]);
    }
}

void ImageKeeper::set_backs(QVector<QLabel *> cards_images)
{
    foreach (QLabel *element, cards_images) {
//        emit deal_card(element);
//        QApplication::processEvents();
        deal_card_animation(element);

        element->setPixmap(*pictures[BACK]);
    }
}

void ImageKeeper::set_back(QLabel *card_image)
{
//    emit deal_card(card_image);
//    QApplication::processEvents();
    deal_card_animation(card_image);

    card_image->setPixmap(*pictures[BACK]);
}

void ImageKeeper::flip_cards(vector<const Card *> &cards,
                             QVector<QLabel *> cards_images)
{
    // TODO

    // This slot inserts images according to cards in cards_images at the
    // same order.

    if (cards.size() == (unsigned)cards_images.size()) {
        card_it card = cards.begin();
        foreach (QLabel *element, cards_images) {
            element->setPixmap(*get_card_image(*card));
            ++card;
        }
    } else {
        QMessageBox::warning(new QWidget(), "Error",
                             "Error in slot of ImageKeeper: lenght mismatch.");
    }
}

void ImageKeeper::flip_card(const Card *card, QLabel *card_image)
{
    // TODO

    card_image->setPixmap(*get_card_image(card));
}

void ImageKeeper::deal_card_animation(QLabel *card)
{

    QPropertyAnimation anim(animated_card, "pos");

    const QPoint old_pos = animated_card->pos();

    anim.setDuration(ANIMATION_DURATION);
    anim.setStartValue(animated_card->pos());
    anim.setEndValue(card->mapTo(main_window, QPoint(0, 0)));
    anim.setEasingCurve(QEasingCurve::OutCirc);

    connect(&anim, SIGNAL(finished()), event_loop, SLOT(quit()));
    anim.start();
    event_loop->exec();
    anim.disconnect();

    animated_card->move(old_pos);
    //QApplication::processEvents();
}

void ImageKeeper::set_dealer_puck(QLabel *puck)
{
    puck->setPixmap(*pictures[DEALER_PUCK]);
}

void ImageKeeper::set_blind_puck(QLabel *puck, Player::blind_t blind)
{
    if (blind == Player::BIG) {
        puck->setPixmap(*pictures[BIG_BLIND_PUCK]);
    } else {
        puck->setPixmap(*pictures[SMALL_BLIND_PUCK]);
    }
}

void ImageKeeper::clear_puck(QLabel *puck)
{
    puck->setPixmap(*pictures[BLANK]);
}

//------------------------------------------

SoundKeeper::SoundKeeper()
{

}

SoundKeeper::~SoundKeeper()
{

}
