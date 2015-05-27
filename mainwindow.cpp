#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"
#include "QPainter"
#include "QPicture"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    test.check_shuffle();
    test.check_combinations();

    QPixmap img(71, 96);
    QPainter painter(&img);
    QPixmap pic("1_strip4.png");
    painter.drawPixmap(0, 0, pic, 71, 0, 71, 96);

    ui->label->setFixedSize(img.size());
    ui->label->setPixmap(img);

}

//class mywidget: public QWidget
//{
//    mywidget(QObject parent = 0) : QWidget(parent)
//    {}
//    paintEvent();
//};
