/*
 * Created by Maxim Kolotilin on 12.04.2015
 * e-mail: maxkolmail@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0.
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * It's a part of Texas Hold'em project
 *
 */

#include "src/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    try {
        QApplication app(argc, argv);
        MainWindow window;

        window.show();

        return app.exec();
    }
    catch(std::exception *exception) {
        QMessageBox::warning(new QWidget(), "Error",
                             "There is no pictures! Please, move folder \"res\""
                             " to the folder with executable file.");
        return 1;
    }
}
