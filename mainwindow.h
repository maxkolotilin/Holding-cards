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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //Test test;
    QVector<Player *> players_pool;
    ImageKeeper *ik;
    QGame *game;
};

#endif // MAINWINDOW_H
