#include "fatigue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fatigue w;
    w.show();
    return a.exec();
}
