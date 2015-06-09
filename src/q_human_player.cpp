/*
 * Created by Maxim Kolotilin on 02.06.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for q_human_player.h
 *
 */

#include "q_human_player.h"

QHumanPlayer::QHumanPlayer(QPushButton *all_in, QPushButton *raise,
                           QPushButton *call, QPushButton *fold,
                           QLabel *name_lb, QLabel *stack_lb, QLabel *action_lb,
                           QLabel *puck_lb, QLabel *bet_size_lb,
                           QSlider *bet_size_slider,
                           QWidget *bar, QWidget *button_bar,
                           string name, int id, chips_t stack,
                           PocketCards *hand, ImageKeeper *ik, SoundKeeper *sk,
                           QObject *parent /* = 0 */)
    : HumanPlayer(name, id, stack, hand, parent)
{
    sound_keeper = sk;
    name_label = name_lb;
    name_label->setText(QString::fromStdString(name));
    stack_label = stack_lb;
    action_label = action_lb;
    bet_size_label = bet_size_lb;
    puck_label = puck_lb;
    bet_slider = bet_size_slider;
    this->bar = bar;
    this->button_bar = button_bar;
    this->bar->hide();
    this->button_bar->setDisabled(true);

    QPalette focus_palette;
    focus_palette.setBrush(QPalette::Background,
                           ik->get_picture(ImageKeeper::BAR_BACKGROUND)->
                           scaled(this->bar->size(), Qt::IgnoreAspectRatio));
    this->bar->setPalette(focus_palette);

    event_loop = new QEventLoop();

    connect(this, SIGNAL(update_stack(int)),
            stack_label, SLOT(setNum(int)));
    connect(this, SIGNAL(update_action(QString)),
            action_label, SLOT(setText(QString)));

    connect(all_in, SIGNAL(clicked()),
            event_loop, SLOT(quit()));
    connect(raise, SIGNAL(clicked()),
            event_loop, SLOT(quit()));
    connect(call, SIGNAL(clicked()),
            event_loop, SLOT(quit()));
    connect(fold, SIGNAL(clicked()),
            event_loop, SLOT(quit()));

    connect(all_in, SIGNAL(clicked()),
            this, SLOT(all_in()));
    connect(raise, SIGNAL(clicked()),
            this, SLOT(raise()));
    connect(call, SIGNAL(clicked()),
            this, SLOT(call()));
    connect(fold, SIGNAL(clicked()),
            this, SLOT(fold()));

//    connect(all_in, SIGNAL(clicked()),
//            sk, SLOT(play_all_in_sound()));
//    connect(raise, SIGNAL(clicked()),
//            sk, SLOT(play_raise_sound()));
//    connect(call, SIGNAL(clicked()),
//            sk, SLOT(play_call_sound()));
//    connect(fold, SIGNAL(clicked()),
//            sk, SLOT(play_fold_sound()));

    connect(bet_size_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(calculate_bet_size(int)));
    connect(this, SIGNAL(send_bet_size(int)),
            bet_size_lb, SLOT(setNum(int)));

    connect(this, SIGNAL(set_blind_puck(QLabel*, Player::blind_t)),
            ik, SLOT(set_blind_puck(QLabel*, Player::blind_t)));
    connect(this, SIGNAL(set_dealer_puck(QLabel*)),
            ik, SLOT(set_dealer_puck(QLabel*)));
    connect(this, SIGNAL(clear_puck(QLabel*)),
            ik, SLOT(clear_puck(QLabel*)));

    connect(this, SIGNAL(i_am_winner(QLabel*)),
            ik, SLOT(set_winner_image(QLabel*)));

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    name_label->setText(QString::fromStdString(name));
    QApplication::processEvents();
}

QHumanPlayer::~QHumanPlayer()
{
    disconnect();
    bar->hide();
    event_loop->disconnect();
    delete event_loop;
}

chips_t QHumanPlayer::stake(chips_t max_bet_in_round)
{
    chips_t amount = Player::stake(max_bet_in_round);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
    return amount;
}

chips_t QHumanPlayer::blind(blind_t type)
{
    chips_t blind = Player::blind(type);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    emit set_blind_puck(puck_label, type);
    QApplication::processEvents();
    return blind;
}

QHumanPlayer::action_t QHumanPlayer::action(chips_t max_bet_in_round,
                                            chips_t raise_size)
{
    if (is_in_game) {
        sound_keeper->play_activate_human_sound();

        // focus on current bar
        bar->setAutoFillBackground(true);
        button_bar->setEnabled(true);
        QApplication::processEvents();

        this->max_bet_in_round = max_bet_in_round;
        this->raise_size = raise_size;

        calculate_bet_size(bet_slider->value());

        event_loop->exec();

        stake(max_bet_in_round);

        // unfocus
        bar->setAutoFillBackground(false);
        button_bar->setDisabled(true);
        QApplication::processEvents();
    }

    return last_action;
}

void QHumanPlayer::fold()
{
    set_fold();

    sound_keeper->play_fold_sound();
    bar->setDisabled(true);
}

void QHumanPlayer::all_in()
{
    set_all_in();

    sound_keeper->play_all_in_sound();
}

void QHumanPlayer::call()
{
    set_call(max_bet_in_round);

    if (max_bet_in_round != 0) {
        sound_keeper->play_call_sound();
    } else {
        sound_keeper->play_check_sound();
    }
}

void QHumanPlayer::raise()
{
    set_raise(max_bet_in_round, raise_size, (chips_t)bet_size_label->text().toInt());

    if (max_bet_in_round == 0 && last_action.amount == 0) {
        // Player made wrong action. It is check.
        // Method stake() will correct it
        sound_keeper->play_check_sound();
    } else {
        sound_keeper->play_raise_sound();
    }
}

void QHumanPlayer::calculate_bet_size(int percent)  // 0 - 100
{
    const double FROM_PERCENTS = 100.0;

    // (call + min raise) + (remaining part of stack)
    // remaining part of stack is a multiple of min_bet
    chips_t min_raise = max_bet_in_round - my_bets_in_round + raise_size;
    emit send_bet_size(min_raise + ((int)((stack - min_raise) * percent /
                                     FROM_PERCENTS) / min_bet) * min_bet);
}

void QHumanPlayer::reset_player()
{
    Player::reset_player();
    max_bet_in_round = 0;
    raise_size = 0;

    bar->setEnabled(true);

    emit update_stack(stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    emit clear_puck(puck_label);
    QApplication::processEvents();
}

void QHumanPlayer::reset_last_action()
{
    Player::reset_last_action();

    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
}

void QHumanPlayer::set_dealer(bool switcher)
{
    Player::set_dealer(switcher);

    if (is_dealer) {
        emit set_dealer_puck(puck_label);
    } else {
        emit clear_puck(puck_label);
    }
    QApplication::processEvents();
}

void QHumanPlayer::set_winner()
{
    emit i_am_winner(action_label);
    QApplication::processEvents();
}
