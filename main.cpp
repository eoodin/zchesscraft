#include <QApplication>
#include "zchesscraft.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZChessCraft w;
    w.show();
    return a.exec();
}
