#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"
#include "QPainter"
#include "QPicture"
#include "QScreen"
#include "keepers.h"
#include "src/card.h"
#include "q_cards_on_table.h"

#include "src/game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QScreen screen();
//    QScreen g = new QScreen();
            //QApplication::screens().back()->availableSize();
    //ui->label->setText(QString(QApplication::screens().size()));
    qDebug() << QApplication::screens().size() << '\n';
    QPixmap bkgnd("res/pic/table.png");
    //this->setFixedSize(QApplication::screens().back()->availableSize());
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ImageKeeper ik;
    QPixmap* pic = ik.get_card_image(new Card(12,3));



//   // QPixmap pixmap(ui->bar_1->size());
//    QPainter painter(ui->name_bar_1);
//    painter.setPen(QPen(Qt::yellow, 5));
//    painter.drawEllipse(1, 1, 10, 10);
//    painter.end();
//    //QPalette palette(ui->bar_1->palette());
//    //ui->bar_1->palette().


    ui->card_1_bar_1->setPixmap(*pic);
    ui->card_2_bar_1->setPixmap(*pic);
    ui->card_1_bar_10->setPixmap(*pic);
    ui->card_2_bar_10->setPixmap(*pic);
    ui->card_1_bar_2->setPixmap(*pic);
    ui->card_2_bar_2->setPixmap(*pic);
    ui->card_1_bar_3->setPixmap(*pic);
    ui->card_2_bar_3->setPixmap(*pic);
    ui->card_1_bar_4->setPixmap(*pic);
    ui->card_2_bar_4->setPixmap(*pic);
    ui->card_1_bar_5->setPixmap(*pic);
    ui->card_2_bar_5->setPixmap(*pic);
    ui->card_1_bar_6->setPixmap(*pic);
    ui->card_2_bar_6->setPixmap(*pic);
    ui->card_1_bar_7->setPixmap(*pic);
    ui->card_2_bar_7->setPixmap(*pic);
    ui->card_1_bar_8->setPixmap(*pic);
    ui->card_2_bar_8->setPixmap(*pic);
    ui->card_1_bar_9->setPixmap(*pic);
    ui->card_2_bar_9->setPixmap(*pic);
    ui->flopcard_1->setPixmap(*pic);
    ui->flopcard_2->setPixmap(*pic);
    ui->flopcard_3->setPixmap(*pic);
    ui->turncard->setPixmap(*pic);
    ui->rivercard->setPixmap(*pic);
    ui->name_bar_1->setText("MaximKa");

    ui->card_1_bar_1->setDisabled(true);
    ui->bar_2->hide();

//    Game game;
//    game.add_player(new HumanPlayer(1, 0));
//    game.search_for_losers();

    pic = ik.get_blank();
    ui->card_1_bar_10->setPixmap(*pic);

    pic = ik.get_card_back();
    ui->card_1_bar_3->setPixmap(*pic);
    *pic = pic->scaled(90, 130, Qt::KeepAspectRatio);
    ui->card_2_bar_3->setPixmap(*pic);

    Deck_of_cards deck;
    deck.shuffle();

    QCardsOnTable cards(ui->flopcard_1, ui->flopcard_2, ui->flopcard_3,
                        ui->turncard, ui->rivercard, &ik);

    QObject::connect(&cards, SIGNAL(clear_cards_on_table(QVector<QLabel*>&)),
                     &ik, SLOT(set_backs(QVector<QLabel*>&)));
    QObject::connect(&cards, SIGNAL(update_cards_on_table(vector<const Card*>&,QVector<QLabel*>&)),
                     &ik, SLOT(set_faces(vector<const Card*>&,QVector<QLabel*>&)));
    cards.set_preflop();
//    cards.set_flop(&deck);
//    cards.set_turn(&deck);
//    cards.set_river(&deck);


}

MainWindow::~MainWindow()
{
    delete ui;
}



//class mywidget: public QWidget
//{
//    mywidget(QObject parent = 0) : QWidget(parent)
//    {}
//    paintEvent();
//};
