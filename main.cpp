#include "billsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BillSystem w;
    w.show();
    return a.exec();
}
