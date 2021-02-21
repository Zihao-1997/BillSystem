#include "billsystem.h"

#include <QApplication>
#include "clientinfomodel.h"
#include "billmanagementwidget.h"
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    BillSystem w;
//    w.show();

//    QTableView view;
//    ClientInfoModel model;
//    view.setModel(&model);
//    view.resize(650, 400);
//    view.show();

//    ClientInfoWidget w;
//    w.resize(650, 400);
//    w.show();

    BillManagementWidget w;
    w.show();

//    QTableView view;
//    BillManagementModel w(nullptr, BILL_TYPE_OUTSOLE);
//    view.setModel(&w);
//    view.show();

    return a.exec();
}
