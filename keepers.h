#ifndef KEEPERS_H
#define KEEPERS_H

#include <QWidget>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include "src/card.h"

class ImageKeeper
{
public:
    enum choice_t { VAR_1 };

    ImageKeeper(choice_t choice = VAR_1);
    ~ImageKeeper();
    QPixmap* get_card_image(Card card);
private:
    QVector<QVector<QPixmap*>> cards_img;
    const QString PATH = "res/pic/";
    const int CARD_HEIGHT = 96;
    const int CARD_WIDTH = 71;
};

class SoundKeeper
{
public:
    enum choice_t { VAR_1 };

    SoundKeeper(choice_t choice = VAR_1);
    ~SoundKeeper();
private:
    const QString PATH = "res/sound/";

};

#endif // KEEPERS_H
