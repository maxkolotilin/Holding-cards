#ifndef QHUMANPLAYER_H
#define QHUMANPLAYER_H

#include <QObject>
#include <QPushButton>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include <QVector>
#include <QEventLoop>
#include "src/player.h"

class QHumanPlayer : public QObject, HumanPlayer
{
    Q_OBJECT
public:
    explicit QHumanPlayer(QPushButton *all_in, QPushButton *raise,
                          QPushButton *call, QPushButton *fold,
                          QLabel *name_lb, QLabel *stack_lb, QLabel *action_lb,
                          QLabel *bet_size_lb, QSlider *bet_size_slider,
                          QWidget *bar,
                          string name, int id, chips_t stack,
                          Pocket_cards *hand, QObject *parent = 0);
    ~QHumanPlayer();

    action_t action(chips_t max_bet_in_round);
    chips_t blind(blind_t type);
    chips_t stake(action_t action);
    void reset_player();
    //void set_dealer(bool switcher);

private:
    //QString action_to_string(action_t act);

    QLabel *name_label;
    QLabel *stack_label;
    QLabel *action_label;
    QLabel *bet_size_label;
    QWidget *bar;

    QEventLoop *event_loop;

signals:
    void update_stack(chips_t amount);
    void update_action(QString &act);
    void send_bet_size(chips_t amount);

public slots:
    void raise();
    void fold();
    void call();
    void all_in();

    void calculate_bet_size(int percent);

};

#endif // QHUMANPLAYER_H
