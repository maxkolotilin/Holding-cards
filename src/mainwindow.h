/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 * This file contains class of main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
// #include <src/core/Test.h>
#include "keepers.h"
#include "src/core/card.h"
#include "q_cards_on_table.h"
#include "q_pocket_cards.h"
#include "q_computer_player.h"
#include "q_game.h"
#include "q_human_player.h"

class QGame;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    //Test test;
    QVector<Player *> players_pool;
    ImageKeeper *ik;
    SoundKeeper *sk;
    QGame *game;

signals:
    void any_button_pushed();

private slots:
    void on_pushButton_clicked();
    void update_speed(int slider_position);
    void keyPressEvent(QKeyEvent *pe);
    void mousePressEvent(QMouseEvent *me);
};

#endif // MAINWINDOW_H
