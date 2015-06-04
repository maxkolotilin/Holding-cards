#include "keepers.h"
#include <QApplication>
#include <QMessageBox>
#include <QPainter>

ImageKeeper::ImageKeeper(QWidget *w, QLabel *animated_card, bool scale /* = true */,
                         QObject *parent /* = 0 */, choice_t choice /* = 0 */)
    : QObject(parent), cards_img(QVector<QVector<QPixmap*>>(Card::NUMBER_OF_FACE,
                                         QVector<QPixmap*>(Card::NUMBER_OF_SUIT)))
{
    for (int face = 0; face < Card::NUMBER_OF_FACE; ++face) {
        for (int suit = 0; suit < Card::NUMBER_OF_SUIT; ++suit)
        {
            cards_img[face][suit] = new QPixmap(PATH + QString::number(face) +
                                                QString::number(suit) + ".png");
        }
    }
    back = new QPixmap(PATH + "back.bmp");
    blank = new QPixmap(PATH + "blank.png");

    if (scale) {
        scale_cards(DEFAULT_CARD_WIDTH, DEFAULT_CARD_HEIGHT);
    }

    this->animated_card = animated_card;
    this->animated_card->setPixmap(*back);

    event_loop = new QEventLoop();

    connect(this, SIGNAL(drop_card(QLabel*)),
            this, SLOT(drop_card_animation(QLabel*)));

    this->w = w;
}

ImageKeeper::~ImageKeeper()
{
    delete event_loop;
}

void ImageKeeper::scale_cards(int width, int height)
{
    *back = back->scaled(width, height, Qt::IgnoreAspectRatio);
    *blank = blank->scaled(width, height, Qt::IgnoreAspectRatio);
    foreach (QVector<QPixmap *> vector, cards_img) {
        foreach (QPixmap *pic, vector) {
            *pic = pic->scaled(width, height, Qt::IgnoreAspectRatio);
        }
    }
}

QPixmap* ImageKeeper::get_card_image(const Card *card)
{
    return cards_img[card->get_face()][card->get_suit()];
}

// slots  ========================================================

void ImageKeeper::set_faces(vector<const Card *> &cards,
                            QVector<QLabel *> &cards_images)
{
    // This function inserts images according to cards in cards_images at the
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

void ImageKeeper::set_face(const Card *card, QLabel *card_image)
{
    card_image->setPixmap(*get_card_image(card));
}

void ImageKeeper::clear_cards(QVector<QLabel *> &cards_images)
{
    foreach (QLabel *element, cards_images) {
        element->setPixmap(*blank);
    }
}

void ImageKeeper::set_backs(QVector<QLabel *> &cards_images)
{
    foreach (QLabel *element, cards_images) {
        emit drop_card(element);
        QApplication::processEvents();
        element->setPixmap(*back);
    }
}

void ImageKeeper::set_back(QLabel *card_image)
{
    emit drop_card(card_image);
    QApplication::processEvents();
    card_image->setPixmap(*back);
}

void ImageKeeper::turn_cards(vector<const Card *> &cards,
                             QVector<QLabel *> &cards_images)
{
    // uncomplited
//    QPropertyAnimation anim(animated_card, "yRotation");
//    anim.setDuration(333);
//    QPainter painter(animated_card);
//    anim.setStartValue(painter.shear(0,0));
//    anim.setEndValue(painter.shear(1.0,0));
//    anim.start();
//    connect(&anim, SIGNAL(finished()), event_loop, SLOT(quit()));
//    event_loop->exec();
//    anim.disconnect();
    for (int i = 0; i < cards_images.size(); ++i) {
        set_face(cards[i], cards_images[i]);
    }
}

void ImageKeeper::drop_card_animation(QLabel *card)
{
    QPropertyAnimation anim(animated_card, "pos");
    anim.setDuration(333);
    const QPoint old_pos = animated_card->pos();
    anim.setStartValue(animated_card->pos());
    //QMessageBox::about(new QWidget(), QString::number(card->pos().ry()), QString::number(card->pos().rx()));
    anim.setEndValue(card->mapTo(w, QPoint(0, 0)));
    anim.setEasingCurve(QEasingCurve::OutCirc);
    anim.start();
    connect(&anim, SIGNAL(finished()), event_loop, SLOT(quit()));
    event_loop->exec();
    anim.disconnect();
    animated_card->move(old_pos);
    QApplication::processEvents();
}

//------------------------------------------

SoundKeeper::SoundKeeper()
{

}

SoundKeeper::~SoundKeeper()
{

}
