/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class inherited from ComputerPlayer
 * Add interaction with GUI
 *
 */

#ifndef QCOMPUTERPLAYER_H
#define QCOMPUTERPLAYER_H

#include <QObject>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include <QTimer>
#include <thread>
#include <chrono>
#include <QApplication>
#include "src/core/player.h"
#include "keepers.h"

class QComputerPlayer : public ComputerPlayer
{
    Q_OBJECT
public:
    explicit QComputerPlayer(QLabel *name_lb, QLabel *stack_lb,
                             QLabel *action_lb, QLabel *puck_lb,
                             QWidget *bar, string name, int id,
                             chips_t stack, PocketCards *hand,
                             const chips_t *pot, const chips_t *total_bets,
                             const CardsOnTable::round_t *round,
                             Evaluator *evaluator, ImageKeeper *ik,
                             SoundKeeper *sk, QObject *parent = 0);
    ~QComputerPlayer();

    action_t action(chips_t max_bet_in_round, chips_t raise_size);
    chips_t blind(blind_t type);
    chips_t stake(chips_t max_bet_in_round);
    void set_dealer(bool switcher);
    void reset_player();
    void reset_last_action();
    void enable()
    {
        bar->show();
    }

    void set_fold();
    void set_raise(chips_t max_bet_in_round, chips_t raise_size,
                   chips_t bet);
    void set_call(chips_t max_bet_in_round);
    void set_all_in();


private:
    QWidget *bar;

    QLabel *name_label;
    QLabel *stack_label;
    QLabel *action_label;
    QLabel *puck_label;

    QPixmap bar_background;

    SoundKeeper *sound_keeper;

signals:
    void update_stack(int amount);
    void update_action(QString act);

    void set_dealer_puck(QLabel *puck);
    void set_blind_puck(QLabel *puck, Player::blind_t blind);
    void clear_puck(QLabel *puck);

public slots:
};

#endif // QCOMPUTERPLAYER_H
