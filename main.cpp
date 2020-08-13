#include "tb_mon_sw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tb_mon_sw w;
    w.hide();
    return a.exec();
}
