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
                                 SoundKeeper *sk, QObject *parent)
    : ComputerPlayer(name, id, stack, pot, total_bets,round, hand, evaluator,
                     parent)
{
    name_label = name_lb;
    name_label->setText(QString::fromStdString(name));
    stack_label = stack_lb;
    action_label = action_lb;
    puck_label = puck_lb;
    this->bar = bar;
    this->bar->hide();

    // set background
    QPalette focus_palette;
    focus_palette.setBrush(QPalette::Background,
                           ik->get_picture(ImageKeeper::BAR_BACKGROUND)->
                           scaled(this->bar->size(), Qt::IgnoreAspectRatio));
    this->bar->setPalette(focus_palette);

    sound_keeper = sk;

    // update labels
    connect(this, SIGNAL(update_stack(int)),
            stack_label, SLOT(setNum(int)));
    connect(this, SIGNAL(update_action(QString)),
            action_label, SLOT(setText(QString)));
    // update puck
    connect(this, SIGNAL(set_blind_puck(QLabel*, Player::blind_t)),
            ik, SLOT(set_blind_puck(QLabel*,Player::blind_t)));
    connect(this, SIGNAL(set_dealer_puck(QLabel*)),
            ik, SLOT(set_dealer_puck(QLabel*)));
    connect(this, SIGNAL(clear_puck(QLabel*)),
            ik, SLOT(clear_puck(QLabel*)));
    // set winner label
    connect(this, SIGNAL(i_am_winner(QLabel*)),
            ik, SLOT(set_winner_image(QLabel*)));

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
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

const int QComputerPlayer::DELAY;

QComputerPlayer::action_t QComputerPlayer::action(chips_t max_bet_in_round,
                                                  chips_t raise_size)
{
    // focus on current bar
    bar->setAutoFillBackground(true);
    QApplication::processEvents();

    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

    // unfocus
    bar->setAutoFillBackground(false);
    QApplication::processEvents();

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

void QComputerPlayer::reset_last_action()
{
    Player::reset_last_action();

    emit update_action(QString::fromStdString(action_to_string(last_action)));
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

    sound_keeper->play_fold_sound();

    bar->setDisabled(true);
}

void QComputerPlayer::set_all_in()
{
    Player::set_all_in();

    sound_keeper->play_all_in_sound();
}

void QComputerPlayer::set_call(chips_t max_bet_in_round)
{
    Player::set_call(max_bet_in_round);

    if (max_bet_in_round != 0) {
        sound_keeper->play_call_sound();
    } else {
        sound_keeper->play_check_sound();
    }
}

void QComputerPlayer::set_raise(chips_t max_bet_in_round,
                                chips_t raise_size, chips_t bet)
{
    Player::set_raise(max_bet_in_round, raise_size, bet);

    if (max_bet_in_round == 0 && last_action.amount == 0) {
        // Player made wrong action. It is check.
        // Method stake() will correct it
        sound_keeper->play_check_sound();
    } else {
        sound_keeper->play_raise_sound();
    }
}

void QComputerPlayer::set_winner()
{
    emit i_am_winner(action_label);
    QApplication::processEvents();
}
