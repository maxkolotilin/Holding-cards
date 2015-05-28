#include "keepers.h"

ImageKeeper::ImageKeeper(choice_t choice /* = 0 */)
    :cards_img(QVector<QVector<QPixmap*>>(Card::NUMBER_OF_FACE,
                                QVector<QPixmap*>(Card::NUMBER_OF_SUIT)))
{
    for (int face = 0; face < Card::NUMBER_OF_FACE; ++face) {
        for (int suit = 0; suit < Card::NUMBER_OF_SUIT; ++suit)
        {
            cards_img[face][suit] = new QPixmap(PATH + QString::number(face) +
                                                QString::number(suit) + ".png");
        }

    }
}

QPixmap* ImageKeeper::get_card_image(Card card)
{
    return cards_img[card.get_face()][card.get_suit()];
}

ImageKeeper::~ImageKeeper()
{

}

//------------------------------------------

SoundKeeper::SoundKeeper(choice_t choice)
{

}

SoundKeeper::~SoundKeeper()
{

}
