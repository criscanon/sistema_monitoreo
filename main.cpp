#include "proyecto.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Proyecto w;
    w.show();
    return a.exec();
}
