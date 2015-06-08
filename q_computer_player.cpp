/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for q_computer_player.h
 *
 */

#include "q_computer_player.h"

QComputerPlayer::QComputerPlayer(QLabel *name_lb, QLabel *stack_lb,
                                 QLabel *action_lb, QLabel *puck_lb, QWidget *bar,
                                 std::string name, int id, chips_t stack,
                                 PocketCards *hand, const chips_t *pot,
                                 const chips_t *total_bets,
                                 const CardsOnTable::round_t *round,
                                 Evaluator *evaluator, ImageKeeper *ik,
                                 QObject *parent)
    : ComputerPlayer(name, id, stack, pot, total_bets,round, hand, evaluator,
                     parent)
{
    name_label = name_lb;
    stack_label = stack_lb;
    action_label = action_lb;
    puck_label = puck_lb;
    this->bar = bar;
    bar->hide();

    connect(this, SIGNAL(update_stack(int)),
            stack_label, SLOT(setNum(int)));
    connect(this, SIGNAL(update_action(QString)),
            action_label, SLOT(setText(QString)));
    connect(this, SIGNAL(set_blind_puck(QLabel*, Player::blind_t)),
            ik, SLOT(set_blind_puck(QLabel*,Player::blind_t)));
    connect(this, SIGNAL(set_dealer_puck(QLabel*)),
            ik, SLOT(set_dealer_puck(QLabel*)));
    connect(this, SIGNAL(clear_puck(QLabel*)),
            ik, SLOT(clear_puck(QLabel*)));

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    name_label->setText(QString::fromStdString(name));
    QApplication::processEvents();
}

QComputerPlayer::~QComputerPlayer()
{
    disconnect();
    bar->hide();
}

chips_t QComputerPlayer::stake(chips_t max_bet_in_round)
{
    chips_t amount = Player::stake(max_bet_in_round);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();

    return amount;
}

chips_t QComputerPlayer::blind(blind_t type)
{
    chips_t blind = Player::blind(type);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    emit set_blind_puck(puck_label, type);
    QApplication::processEvents();

    return blind;
}

QComputerPlayer::action_t QComputerPlayer::action(chips_t max_bet_in_round,
                                                  chips_t raise_size)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return ComputerPlayer::action(max_bet_in_round, raise_size);
}

void QComputerPlayer::reset_player()
{
    Player::reset_player();

    bar->setEnabled(true);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    emit clear_puck(puck_label);
    QApplication::processEvents();
}

void QComputerPlayer::set_dealer(bool switcher)
{
    Player::set_dealer(switcher);

    if (is_dealer) {
        emit set_dealer_puck(puck_label);
    } else {
        emit clear_puck(puck_label);
    }
    QApplication::processEvents();
}

void QComputerPlayer::set_fold()
{
    Player::set_fold();

    bar->setDisabled(true);
}
