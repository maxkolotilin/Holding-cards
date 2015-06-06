#include "q_computer_player.h"
#include <QTimer>
#include <thread>
#include <chrono>
#include <QApplication>

QComputerPlayer::QComputerPlayer(QLabel *name_lb, QLabel *stack_lb,
                                 QLabel *action_lb, QWidget *bar,
                                 std::string name, int id, chips_t stack,
                                 PocketCards *hand, const chips_t *pot,
                                 const chips_t *total_bets,
                                 const CardsOnTable::round_t *round,
                                 Evaluator *evaluator, QObject *parent)
    : ComputerPlayer(name, id, stack, pot, total_bets,round,
                                      hand, evaluator)
{
    name_label = name_lb;
    stack_label = stack_lb;
    action_label = action_lb;
    this->bar = bar;
    bar->hide();

    connect(this, SIGNAL(update_stack(int)),
            stack_label, SLOT(setNum(int)), Qt::DirectConnection);
    connect(this, SIGNAL(update_action(QString)),
            action_label, SLOT(setText(QString)), Qt::DirectConnection);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    name_label->setText(QString::fromStdString(name));
    QApplication::processEvents();
}

QComputerPlayer::~QComputerPlayer()
{
    bar->hide();
}

chips_t QComputerPlayer::stake(action_t action)
{
    chips_t amount = Player::stake(action);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(action)));
    QApplication::processEvents();
    return amount;
}

chips_t QComputerPlayer::blind(blind_t type)
{
    chips_t blind = Player::blind(type);

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
    return blind;
}

QComputerPlayer::action_t QComputerPlayer::action(chips_t max_bet_in_round)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return ComputerPlayer::action(max_bet_in_round);
}

void QComputerPlayer::reset_player()
{
    Player::reset_player();

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
}
