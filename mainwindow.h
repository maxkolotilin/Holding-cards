#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/Test.h>

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
    Test test;
};

#endif // MAINWINDOW_H
