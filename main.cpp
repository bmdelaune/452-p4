#include "mainwindow.h"
#include <QApplication>

int axis_number;

int main(int argc, char *argv[])
{
    axis_number = 1;
    QApplication a(argc, argv);
    mainWindow w;
    w.show();
    return a.exec();
}
