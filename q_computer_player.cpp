#include "q_computer_player.h"
#include <QTimer>
#include <thread>
#include <chrono>
#include <QApplication>

QComputerPlayer::QComputerPlayer(QLabel *name_lb, QLabel *stack_lb,
                                 QLabel *action_lb, QWidget *bar,
                                 std::string name, int id, chips_t stack,
                                 Pocket_cards *hand, const chips_t *pot,
                                 const chips_t *total_bets,
                                 const Cards_on_table::Round_t *round,
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
    if (last_action.action == FOLD) {
        last_action = { true, NONE, 0 };
    }

    if (last_action.action != NONE) {
        this->max_bet_in_round = max_bet_in_round;

        if(*round == Cards_on_table::PREFLOP) {
            if(check_top_10_hands()) {
                if ((double)(max_bet_in_round + min_bet) / stack < 0.1) {
                    last_action = { true, RAISE, max_bet_in_round + min_bet -
                                    bets };
                } else {
                    last_action = { true, CALL, max_bet_in_round - bets };
                }
            } else if(check_top_21_hands()) {
                if ((double)(max_bet_in_round + min_bet) / stack < 0.05) {
                    last_action = { true, RAISE, max_bet_in_round + min_bet -
                                    bets };
                } else {
                    last_action = { true, CALL, max_bet_in_round - bets };
                }
            } else if(check_connectors() || check_suited()) {
                if ((double)max_bet_in_round / stack < 0.03) {
                    last_action = { true, RAISE, max_bet_in_round - bets };
                } else {
                    last_action = { true, FOLD, 0 };
                }
            } else {
                last_action = { true, FOLD, 0 };
            }
        } else {
            current_combination(*evaluator);
            count_outs(*evaluator);

            if (strength->get_combination() > Hand_strength::FLUSH) {
                if ((double)(max_bet_in_round + min_bet) / stack < 0.5) {
                    last_action = { true, RAISE, max_bet_in_round + min_bet -
                                    bets };
                } else {
                    last_action = { true, CALL, max_bet_in_round - bets };
                }
            } else if (strength->get_combination() > Hand_strength::PAIR) {
                if ((double)(max_bet_in_round + min_bet) / stack < 0.1) {
                    last_action = { true, RAISE, max_bet_in_round + min_bet -
                                    bets };
                } else {
                    if (check_pot_odds(max_bet_in_round - bets)) {
                        last_action = { true, CALL, max_bet_in_round - bets };
                    } else {
                        last_action = { true, FOLD, 0 };
                    }
                }
            } else {
                if (check_pot_odds(max_bet_in_round - bets)) {
                    last_action = { true, CALL, max_bet_in_round - bets };
                } else {
                    last_action = { true, FOLD, 0 };
                }
            }

        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        stake(last_action);
    }

    return last_action;
}

void QComputerPlayer::reset_player()
{
    Player::reset_player();

    emit update_stack((int)stack);
    emit update_action(QString::fromStdString(action_to_string(last_action)));
    QApplication::processEvents();
}
