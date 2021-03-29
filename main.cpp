#include "billsystem.h"

#include <QApplication>
#include "clientinfomodel.h"
#include "billmanagementwidget.h"
#include "billwidget.h"
#include "billmodel.h"
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

//    BillManagementModel *model = new BillManagementModel(nullptr, BILL_TYPE_PROCESS);
//    BillProcessModel *modelA = new BillProcessModel();
//    BillOutsoleModel *modelB = new BillOutsoleModel();
//    BillWidget w(nullptr, modelB);
//    w.show();

//    QTableView view;
//    BillManagementModel w(nullptr, BILL_TYPE_OUTSOLE);
//    view.setModel(&w);
//    view.show();

    return a.exec();
}
