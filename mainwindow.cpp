#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"
#include "QPainter"
#include "QPicture"
#include "QScreen"
#include "QTimer"

#include "src/game.h"

class Game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("res/pic/table.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ik = new ImageKeeper();
    game = new QGame(ui->label_pot, ui->label_bets,
                     new QCardsOnTable(ui->flopcard_1, ui->flopcard_2,
                                       ui->flopcard_3, ui->turncard,
                                       ui->rivercard, ik, this),
                     40, this);

    players_pool.push_back(new QComputerPlayer(ui->name_bar_1, ui->stack_bar_1,
                                               ui->action_bar_1, ui->bar_1,
                                               "Computer player 1", 1, 10000,
                                               new QPocketCards(ui->card_1_bar_1,
                                                                ui->card_2_bar_1,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_2, ui->stack_bar_2,
                                               ui->action_bar_2, ui->bar_2,
                                               "Computer player 2", 2, 10000,
                                               new QPocketCards(ui->card_1_bar_2,
                                                                ui->card_2_bar_2,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_3, ui->stack_bar_3,
                                               ui->action_bar_3, ui->bar_3,
                                               "Computer player 3", 3, 10000,
                                               new QPocketCards(ui->card_1_bar_3,
                                                                ui->card_2_bar_3,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_4, ui->stack_bar_4,
                                               ui->action_bar_4, ui->bar_4,
                                               "Computer player 4", 4, 10000,
                                               new QPocketCards(ui->card_1_bar_4,
                                                                ui->card_2_bar_4,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_5, ui->stack_bar_5,
                                               ui->action_bar_5, ui->bar_5,
                                               "Computer player 5", 1, 10000,
                                               new QPocketCards(ui->card_1_bar_5,
                                                                ui->card_2_bar_5,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QHumanPlayer(ui->button_allin, ui->button_raise,
                                            ui->button_call, ui->button_fold,
                                            ui->name_bar_6, ui->stack_bar_6,
                                            ui->action_bar_6, ui->bet_size,
                                            ui->slider_bet_size, ui->bar_6,
                                            "MaximKa", 6, 10000,
                                            new QPocketCards(ui->card_1_bar_6,
                                                             ui->card_2_bar_6,
                                                             ik, this), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_7, ui->stack_bar_7,
                                               ui->action_bar_7, ui->bar_7,
                                               "Computer player 7", 7, 10000,
                                               new QPocketCards(ui->card_1_bar_7,
                                                                ui->card_2_bar_7,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_8, ui->stack_bar_8,
                                               ui->action_bar_8, ui->bar_8,
                                               "Computer player 8", 8, 10000,
                                               new QPocketCards(ui->card_1_bar_8,
                                                                ui->card_2_bar_8,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_9, ui->stack_bar_9,
                                               ui->action_bar_9, ui->bar_9,
                                               "Computer player 9", 9, 10000,
                                               new QPocketCards(ui->card_1_bar_9,
                                                                ui->card_2_bar_9,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_10, ui->stack_bar_10,
                                               ui->action_bar_10, ui->bar_10,
                                               "Computer player 10", 10, 10000,
                                               new QPocketCards(ui->card_1_bar_10,
                                                                ui->card_2_bar_10,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), this));

    game->set_human_ptr(players_pool[5]);
    ui->button_bar->hide();
    ui->deck_bar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ik;
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->button_bar->show();
    ui->deck_bar->show();
    foreach (Player *player, players_pool) {
        player->enable();
        game->add_player(player);
    }
    ui->deck_label->setPixmap(*ik->get_card_back());

//    QEventLoop *loop = new QEventLoop();
//    QTimer *timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
//    timer->start(1);
//    loop->exec();

    QApplication::processEvents();

    Player::set_min_bet(game->get_min_bet());
    game->start();
}
