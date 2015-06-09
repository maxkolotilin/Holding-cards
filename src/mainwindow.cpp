/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * Implementation for mainwindow.h
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPicture>
#include <QScreen>
#include <QTimer>
#include <QPropertyAnimation>
#include <QBitmap>
#include <QThread>
#include <QMetaType>
#include <vector>
#include "src/core/game.h"

using std::vector;




//typedef QVector<QLabel*>* type;
//Q_DECLARE_METATYPE(type)


class Game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showFullScreen();

    sk = new SoundKeeper(this);
    ik = new ImageKeeper(ui->centralWidget, ui->animated_card, sk, this);

    ik->load_pictures();     // throws exception
    ik->scale_cards();

    // set background
    QPixmap bkgnd(*ik->get_picture(ImageKeeper::TABLE));
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    game = new QGame(ui->label_pot, ui->label_bets,
                     new QCardsOnTable(ui->flopcard_1, ui->flopcard_2,
                                       ui->flopcard_3, ui->turncard,
                                       ui->rivercard, ik, this),
                     40, 10,this, ui->label_help_text, sk, this);

    const int PLAYERS_POSITION = 5;

    players_pool.push_back(new QComputerPlayer(ui->name_bar_1, ui->stack_bar_1,
                                               ui->action_bar_1, ui->puck_bar_1,
                                               ui->bar_1,
                                               "Computer player 1", 1, 10000,
                                               new QPocketCards(ui->card_1_bar_1,
                                                                ui->card_2_bar_1,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_2, ui->stack_bar_2,
                                               ui->action_bar_2, ui->puck_bar_2,
                                               ui->bar_2,
                                               "Computer player 2", 2, 10000,
                                               new QPocketCards(ui->card_1_bar_2,
                                                                ui->card_2_bar_2,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_3, ui->stack_bar_3,
                                               ui->action_bar_3, ui->puck_bar_3,
                                               ui->bar_3,
                                               "Computer player 3", 3, 10000,
                                               new QPocketCards(ui->card_1_bar_3,
                                                                ui->card_2_bar_3,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_4, ui->stack_bar_4,
                                               ui->action_bar_4, ui->puck_bar_4,
                                               ui->bar_4,
                                               "Computer player 4", 4, 10000,
                                               new QPocketCards(ui->card_1_bar_4,
                                                                ui->card_2_bar_4,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_5, ui->stack_bar_5,
                                               ui->action_bar_5, ui->puck_bar_5,
                                               ui->bar_5,
                                               "Computer player 5", 1, 10000,
                                               new QPocketCards(ui->card_1_bar_5,
                                                                ui->card_2_bar_5,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QHumanPlayer(ui->button_allin, ui->button_raise,
                                            ui->button_call, ui->button_fold,
                                            ui->name_bar_6, ui->stack_bar_6,
                                            ui->action_bar_6, ui->puck_bar_6,
                                            ui->bet_size, ui->slider_bet_size,
                                            ui->bar_6, "MaximKa", 6, 10000,
                                            new QPocketCards(ui->card_1_bar_6,
                                                             ui->card_2_bar_6,
                                                             ik, this), ik,
                                            sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_7, ui->stack_bar_7,
                                               ui->action_bar_7, ui->puck_bar_7,
                                               ui->bar_7,
                                               "Computer player 7", 7, 10000,
                                               new QPocketCards(ui->card_1_bar_7,
                                                                ui->card_2_bar_7,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_8, ui->stack_bar_8,
                                               ui->action_bar_8, ui->puck_bar_8,
                                               ui->bar_8,
                                               "Computer player 8", 8, 10000,
                                               new QPocketCards(ui->card_1_bar_8,
                                                                ui->card_2_bar_8,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_9, ui->stack_bar_9,
                                               ui->action_bar_9, ui->puck_bar_9,
                                               ui->bar_9,
                                               "Computer player 9", 9, 10000,
                                               new QPocketCards(ui->card_1_bar_9,
                                                                ui->card_2_bar_9,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    players_pool.push_back(new QComputerPlayer(ui->name_bar_10, ui->stack_bar_10,
                                               ui->action_bar_10, ui->puck_bar_10,
                                               ui->bar_10,
                                               "Computer player 10", 10, 10000,
                                               new QPocketCards(ui->card_1_bar_10,
                                                                ui->card_2_bar_10,
                                                                ik, this),
                                               game->get_pot_ptr(),
                                               game->get_bets_ptr(),
                                               game->get_round_ptr(),
                                               game->get_evaluator_ptr(), ik,
                                               sk, this));

    game->set_human_ptr(players_pool[PLAYERS_POSITION]);
    ui->button_bar->hide();
    ui->deck_bar->hide();

    ui->animated_card->move(ui->deck_label->mapToGlobal(ui->deck_label->pos()));
    ui->animated_card->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete ik;
    delete game;
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
    ui->deck_label->setPixmap(*ik->get_picture(ImageKeeper::BACK));
    ui->animated_card->show();

    QApplication::processEvents();
//    QThread *thread = new QThread();
//    ik->moveToThread(thread);
//    thread->start();

    game->start();
}
