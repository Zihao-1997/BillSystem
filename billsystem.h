#ifndef BILLSYSTEM_H
#define BILLSYSTEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include "clientinfomodel.h"

class BillSystem : public QWidget
{
    Q_OBJECT

public:
    BillSystem(QWidget *parent = nullptr);
    ~BillSystem();
    
private:
    void initMainUI(void);
    void setModuleList(QListWidget *listWidget);

private:
    ClientInfoWidget *clientInfoWidget;
    QListWidget *functionalModuleList;
    QStackedWidget *contentWidget;

    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *contentLayout;
};
#endif // BILLSYSTEM_H
