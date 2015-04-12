#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Test.h"

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
    Test test;
    test.check_shuffle();
}
