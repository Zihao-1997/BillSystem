#include "billsystem.h"
#include <QListWidgetItem>

BillSystem::BillSystem(QWidget *parent)
    : QWidget(parent)
{
    initMainUI();
}

BillSystem::~BillSystem()
{
}

void BillSystem::initMainUI(void)
{
    QLabel *titleLabel = new QLabel("账单");

    titleLayout = new QHBoxLayout();
    titleLayout->addWidget(titleLabel);

    clientInfoWidget = new ClientInfoWidget();

    functionalModuleList = new QListWidget();
    setModuleList(functionalModuleList);

    QLabel *functionLabel1 = new QLabel("label1");
    QLabel *functionLabel2 = new QLabel("label2");

    contentWidget = new QStackedWidget();
    contentWidget->addWidget(functionLabel1);
    contentWidget->addWidget(clientInfoWidget);

    contentLayout = new QHBoxLayout();
    contentLayout->addWidget(functionalModuleList);
    contentLayout->addWidget(contentWidget);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(contentLayout);

    connect(functionalModuleList, &QListWidget::currentRowChanged, contentWidget, &QStackedWidget::setCurrentIndex);
}

void BillSystem::setModuleList(QListWidget *listWidget)
{
    QListWidgetItem *billBtn = new QListWidgetItem(listWidget);
    billBtn->setText("BillManagement");
    billBtn->setTextAlignment(Qt::AlignCenter);

    QListWidgetItem *clientBtn = new QListWidgetItem(listWidget);
    clientBtn->setText("ClientInformation");
    clientBtn->setTextAlignment(Qt::AlignCenter);

    QListWidgetItem *supplierBtn = new QListWidgetItem(listWidget);
    supplierBtn->setText("SupplierInformation");
    supplierBtn->setTextAlignment(Qt::AlignCenter);

    QListWidgetItem *adminBtn = new QListWidgetItem(listWidget);
    adminBtn->setText("AdminModule");
    adminBtn->setTextAlignment(Qt::AlignCenter);
}

