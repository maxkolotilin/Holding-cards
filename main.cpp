#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QHBoxLayout* phbx = new QHBoxLayout;
//        phbx->setMargin(0);
//        phbx->setSpacing(0);
//        QLabel* l = new QLabel("dfsaf");
//        l->setFixedSize(50, 20);
//    phbx->addWidget(l);

//    w.setLayout(phbx);
    w.show();

    return a.exec();
}
