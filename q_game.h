#ifndef QGAME_H
#define QGAME_H

#include <QObject>
#include <QLabel>
#include "src/game.h"

class QGame : public Game
{
    Q_OBJECT
public:
    explicit QGame(QLabel *pot, QLabel *bets,
                   Cards_on_table *cards, chips_t min_bet, QObject *parent = 0);
    ~QGame();

    virtual void increase_min_bet();
    virtual void add_to_bets(chips_t bet);
    virtual void add_to_pot(chips_t bets_in_round);
    virtual void reset_bets();
    virtual void reset_pot();

signals:
    void update_bets(int bets);
    void update_pot(int pot);

public slots:
};

#endif // QGAME_H
