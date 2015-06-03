#ifndef QCOMPUTERPLAYER_H
#define QCOMPUTERPLAYER_H

#include <QObject>
#include <QLabel>
#include "src/player.h"

class QComputerPlayer : public ComputerPlayer
{
    Q_OBJECT
public:
    explicit QComputerPlayer(QLabel *name_lb, QLabel *stack_lb,
                             QLabel *action_lb, QWidget *bar,
                             string name, int id, chips_t stack,
                             Pocket_cards *hand, const chips_t *pot,
                             const chips_t *total_bets,
                             const Cards_on_table::Round_t *round,
                             Evaluator *evaluator, QObject *parent = 0);
    ~QComputerPlayer();

    action_t action(chips_t max_bet_in_round);
    chips_t blind(blind_t type);
    chips_t stake(action_t action);
    void reset_player();
    void enable()
    {
        bar->show();
    }

    QWidget *bar;

private:
    //QString action_to_string(action_t act);

    QLabel *name_label;
    QLabel *stack_label;
    QLabel *action_label;

signals:
    void update_stack(int amount);
    void update_action(QString act);

public slots:
};

#endif // QCOMPUTERPLAYER_H
