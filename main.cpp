#include "CubicSpline.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CubicSpline w;
    w.show();
    return a.exec();
}
