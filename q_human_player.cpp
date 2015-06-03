#include "q_human_player.h"
#include <QApplication>

QHumanPlayer::QHumanPlayer(QPushButton *all_in, QPushButton *raise,
                           QPushButton *call, QPushButton *fold,
                           QLabel *name_lb, QLabel *stack_lb, QLabel *action_lb,
                           QLabel *bet_size_lb, QSlider *bet_size_slider,
                           QWidget *bar,
                           string name, int id, chips_t stack,
                           Pocket_cards *hand, QObject *parent /* = 0 */)
    : HumanPlayer(name, id, stack, hand)
{
    name_label = name_lb;
    name_label->setText(QString::fromStdString(name));
    stack_label = stack_lb;
    action_label = action_lb;
    bet_size_label = bet_size_lb;
    this->bar = bar;
    bar->hide();

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

    connect(bet_size_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(calculate_bet_size(int)));       // check disconnect
    connect(this, SIGNAL(send_bet_size(int)),
            bet_size_lb, SLOT(setNum(int)));

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    name_label->setText(QString::fromStdString(name));
    QApplication::processEvents();
}

QHumanPlayer::~QHumanPlayer()
{
    bar->hide();
    event_loop->disconnect();
    delete event_loop;
    disconnect();
}

//QString QHumanPlayer::action_to_string(action_t act)
//{
//    return QString(actions[act.action] + " " + act.amount);
//}

chips_t QHumanPlayer::stake(action_t action)
{
    chips_t amount = Player::stake(action);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(action)));
    QApplication::processEvents();
    return amount;
}

chips_t QHumanPlayer::blind(blind_t type)
{
    chips_t blind = Player::blind(type);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
    return blind;
}

chips_t Player::max_bet_in_round;

QHumanPlayer::action_t QHumanPlayer::action(chips_t max_bet_in_round)
{
    if (last_action.action == FOLD) {
        reset_last_action();
    }
    if (last_action.action != NONE) {
        Player::max_bet_in_round = max_bet_in_round;

        event_loop->exec();

        stake(last_action);
    }

    return last_action;
}

void QHumanPlayer::fold()
{
    last_action = { true, FOLD, 0 };
}

void QHumanPlayer::all_in()
{
    last_action = { true, ALL_IN, stack };
}

void QHumanPlayer::call()
{
    last_action = { true, CALL, max_bet_in_round - bets };
}

void QHumanPlayer::raise()
{
    last_action = { true, RAISE, (chips_t)bet_size_label->text().toInt() };
}

void QHumanPlayer::calculate_bet_size(int percent)
{
    emit send_bet_size((int)(max_bet_in_round + (stack - max_bet_in_round) *
                       percent / 100));          // potentional error
}

void QHumanPlayer::reset_player()
{
    Player::reset_player();

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
}
