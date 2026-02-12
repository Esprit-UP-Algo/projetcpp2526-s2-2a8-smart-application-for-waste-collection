#include "waste.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Waste w;

    w.show();
    return a.exec();
}
