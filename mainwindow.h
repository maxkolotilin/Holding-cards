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
#include <src/Test.h>
#include "keepers.h"
#include "src/card.h"
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    //Test test;
    QVector<Player *> players_pool;
    ImageKeeper *ik;
    QGame *game;

signals:
    void any_button_pushed();

private slots:
    void on_pushButton_clicked();

    void keyPressEvent(QKeyEvent *pe)
    {
        emit any_button_pushed();
    }
};

#endif // MAINWINDOW_H
