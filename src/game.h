#ifndef GAME_H
#define GAME_H

#include "src/player.h"
#include "src/deck_of_cards.h"
#include "src/cards_on_table.h"
#include "src/evaluator.h"
#include <list>

using std::list;

typedef unsigned int chips_t;

class Game
{
public:
    Game();
    ~Game();

    void add_player(Player* pl);
    void start_new_deal();
    void start_trading();

    chips_t get_min_bet() const { return min_bet; }
private:
    chips_t min_bet;
    int number_of_played_hands;
    Deck_of_cards* deck;
    list<Player*> players;
    Cards_on_table* cards_on_table;
    Evaluator* evaluator;
    Cards_on_table::Round_t round;
};

#endif // GAME_H
