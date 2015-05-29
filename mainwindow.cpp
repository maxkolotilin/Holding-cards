#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"
#include "QPainter"
#include "QPicture"
#include "QScreen"
#include "keepers.h"
#include "src/card.h"

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
    QPixmap* pic = new QPixmap("0.png"); //ik.get_card_image(Card(3,1));

    *pic = pic->scaled(96, 152, Qt::KeepAspectRatio);

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
