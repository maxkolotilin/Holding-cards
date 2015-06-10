/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class inherited from HumanPlayer
 * Add interaction with GUI
 *
 */

#ifndef QHUMANPLAYER_H
#define QHUMANPLAYER_H

#include <QObject>
#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include <QVector>
#include <QEventLoop>
#include <QApplication>
#include "src/core/player.h"
#include "keepers.h"

class QHumanPlayer : public HumanPlayer
{
    Q_OBJECT
public:
    QHumanPlayer(QPushButton *all_in, QPushButton *raise, QPushButton *call,
                 QPushButton *fold, QLabel *name_lb, QLabel *stack_lb,
                 QLabel *action_lb, QLabel *puck_lb, QLabel *bet_size_lb,
                 QSlider *bet_size_slider, QWidget *bar, QWidget *button_bar,
                 string name, int id, chips_t stack, PocketCards *hand,
                 ImageKeeper *ik, SoundKeeper *sk, QObject *parent = 0);
    ~QHumanPlayer();

    action_t action(chips_t max_bet_in_round, chips_t raise_size);
    chips_t blind(blind_t type);
    chips_t stake(chips_t max_bet_in_round);
    void reset_player();
    void reset_last_action();
    void set_dealer(bool switcher);
    void set_winner();
    void enable()
    {
        bar->show();
    }

private:
    QWidget *bar;
    QWidget *button_bar;

    QSlider *bet_slider;

    SoundKeeper *sound_keeper;

    QLabel *name_label;
    QLabel *stack_label;
    QLabel *action_label;
    QLabel *bet_size_label;
    QLabel *puck_label;

    QEventLoop *event_loop;

    chips_t max_bet_in_round;
    chips_t raise_size;

signals:
    void update_stack(int amount);
    void update_action(QString act);
    void send_bet_size(int amount);

    void set_dealer_puck(QLabel *puck);
    void set_blind_puck(QLabel *puck, Player::blind_t blind);
    void clear_puck(QLabel *puck);

    void i_am_winner(QLabel *message);

public slots:
    void raise();
    void fold();
    void call();
    void all_in();

    void calculate_bet_size(int percent);

};

#endif // QHUMANPLAYER_H
