#include "solver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Solver w;
    w.show();
    return a.exec();
}
