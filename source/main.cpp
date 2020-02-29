/* Copyright (C) 2020 Dylan Evans - All Rights Reserved
 * You may use, distribute, or modify this code under the terms of the MIT license
 * You should have received a copy of the license with this file. If not, you may visit https://opensource.org/licenses/MIT
*/

#include "solver.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Solver * w;
    try
    {
        w = new Solver();
        w->show();
        return a.exec();
    }
    catch(std::bad_alloc & e)
    {
        QMessageBox::critical(w, "Error", "There is not enough free memory to properly run the program."
                                          "Make sure you have at least 90 MB of freed memory.");
        return 1;
    }
    catch(IOException & e)
    {
        QMessageBox::critical(w, "Error", e.what());
        return 2;
    }
}
