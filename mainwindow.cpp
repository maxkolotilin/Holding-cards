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
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"
#include "QPainter"
#include "QPicture"
#include "QScreen"
#include "QTimer"
#include <QPropertyAnimation>
#include <QBitmap>
#include <QThread>
#include <QMetaType>
#include <vector>

using std::vector;

#include "src/game.h"


typedef QVector<QLabel*>* type;
Q_DECLARE_METATYPE(type)


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

    QPixmap bkgnd_1("res/pic/back.bmp");
    bkgnd_1 = bkgnd_1.scaled(ui->bar_1->size(), Qt::IgnoreAspectRatio);
    QPalette palette_1;
    palette_1.setBrush(QPalette::Background, bkgnd_1);
    ui->bar_1->setPalette(palette_1);

    ik = new ImageKeeper(ui->centralWidget, ui->animated_card);
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

    ui->animated_card->move(ui->deck_label->mapToGlobal(ui->deck_label->pos()));
    ui->animated_card->hide();
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
    ui->animated_card->show();

//    QEventLoop *loop = new QEventLoop();
//    QTimer *timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
//    timer->start(1);
//    loop->exec();

//    ui->animated_card->setPixmap(*ik->get_card_image(new Card(12, 0)));
//    //ui->animated_card->move(ui->deck_label->pos());
//    QPropertyAnimation anim(ui->animated_card, "pos");
//    anim.setDuration(3000);
//    anim.setStartValue(ui->animated_card->pos());
//    anim.setEndValue(ui->horizontalLayout->);
//    anim.setEasingCurve(QEasingCurve::OutCirc);
//    anim.start();
//    QApplication::processEvents();
//    QEventLoop el;
//    connect(&anim, SIGNAL(finished()), &el, SLOT(quit()));
//    el.exec();
    //ui->button_allin->setStyleSheet("qproperty-icon: url(:res/pic/playeraction_blue.png);");
    QPixmap pm("res/pic/playeraction_blue.png");
    QPalette palette;
    palette.setBrush(QPalette::Button, QBrush(pm));
    ui->button_allin->setFlat(true);
    ui->button_allin->setAutoFillBackground(true);
    ui->button_allin->setPalette(palette);
    ui->button_allin->setMask(pm.mask());
    ui->button_allin->setFixedSize(pm.size());
//    QIcon icon(pm);
//    ui->button_allin->setIcon(icon);
//    ui->button_allin->setIconSize(ui->button_allin->size());



    //qRegisterMetaType<QVector<QLabel*> &>();
    QApplication::processEvents();
    QThread *thread = new QThread();
    ik->moveToThread(thread);
    thread->start();

    Player::set_min_bet(game->get_min_bet());
    game->start();
}
