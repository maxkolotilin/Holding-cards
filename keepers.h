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
#include "src/evaluator.h"

class ImageKeeper : public QObject
{
    Q_OBJECT
public:
    enum choice_t { VAR_1 };

    explicit ImageKeeper(QWidget *w, QLabel *animated_card, bool scale = true,
                         QObject *parent = 0, choice_t choice = VAR_1);
    ~ImageKeeper();
    QPixmap* get_card_image(const Card *card);
    void scale_cards(int width, int height);
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
    const QString PATH = "res/pic/";
    const int DEFAULT_CARD_HEIGHT = 130;
    const int DEFAULT_CARD_WIDTH = 90;
    QPixmap *back, *blank;

    QEventLoop *event_loop;
    QLabel *animated_card;

    QWidget *w;

signals:
    void drop_card(QLabel *card);

public slots:
    void drop_card_animation(QLabel *card);
    void set_faces(vector<const Card*> &cards, QVector<QLabel*> &cards_images);
    void set_face(const Card *card, QLabel *card_image);

    void clear_cards(QVector<QLabel*> &cards_images);

    void set_backs(QVector<QLabel*> &cards_images);
    void set_back(QLabel *card_image);

    void turn_cards(vector<const Card*> &cards, QVector<QLabel*> &cards_images);
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
