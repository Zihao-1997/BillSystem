#include "billwidget.h"
#include <QItemSelectionModel>
#include <QDebug>

BillWidget::BillWidget(QWidget *parent, QAbstractTableModel *model)
    : QWidget(parent),
      billModel(model)
{
    billView = new QTableView();
    billView->setModel(billModel);
    initUI();
}

BillWidget::~BillWidget()
{

}

void BillWidget::initUI(void)
{
    addRowBtn = new QPushButton("Add");
    deleteRowBtn = new QPushButton("Delete");
    saveBillBtn = new QPushButton("Save");
    cancelEditBtn = new QPushButton("Cancel");

    upperLayout = new QHBoxLayout();
    upperLayout->addWidget(addRowBtn);
    upperLayout->addWidget(deleteRowBtn);
    upperLayout->addWidget(saveBillBtn);
    upperLayout->addWidget(cancelEditBtn);
    bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(billView);
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(bottomLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setLayout(mainLayout);
//    this->resize(1000, 400);

    connect(addRowBtn, &QPushButton::clicked, this, &BillWidget::onAddBtnClicked);
    connect(deleteRowBtn, &QPushButton::clicked, this, &BillWidget::onDeleteBtnClicked);
    connect(saveBillBtn, &QPushButton::clicked, this, &BillWidget::onSaveBtnClicked);
    connect(cancelEditBtn, &QPushButton::clicked, this, &BillWidget::onCancelBtnClicked);
}

void BillWidget::addRows(int row, int count)
{
    billModel->insertRows(row, count);
}

void BillWidget::deleteRows(int row, int count)
{
    billModel->removeRows(row, count);
}

bool BillWidget::readData(QString fileName)
{
    if (qobject_cast<BillProcessModel *>(billModel)) {
        qDebug() << "BillProcessModel";
        (qobject_cast<BillProcessModel *>(billModel))->xmlRead(fileName);
    }
    else if (qobject_cast<BillOutsoleModel *>(billModel)) {
        qDebug() << "BillOutsoleModel";
        (qobject_cast<BillOutsoleModel *>(billModel))->xmlRead(fileName);
    }

    return true;
}

void BillWidget::saveData(QString fileName)
{
    if (qobject_cast<BillProcessModel *>(billModel)) {
        qDebug() << "BillProcessModel";
        (qobject_cast<BillProcessModel *>(billModel))->xmlClear(fileName);
        (qobject_cast<BillProcessModel *>(billModel))->xmlWrite(fileName);
    }
    else if (qobject_cast<BillOutsoleModel *>(billModel)) {
        qDebug() << "BillOutsoleModel";
        (qobject_cast<BillOutsoleModel *>(billModel))->xmlClear(fileName);
        (qobject_cast<BillOutsoleModel *>(billModel))->xmlWrite(fileName);
    }
    else {
        qDebug() << "nothing";
    }
}

void BillWidget::setXmlPath(QString path)
{
    xmlPath = path;
}

void BillWidget::onAddBtnClicked(void)
{
    QItemSelectionModel *selectionModel = billView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("add row = %d, column = %d", index.row(), index.column());
    addRows(index.row()+1, 1);
}

void BillWidget::onDeleteBtnClicked(void)
{
    QItemSelectionModel *selectionModel = billView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("delete row = %d, column = %d", index.row(), index.column());
    deleteRows(index.row(), 1);
}

void BillWidget::onSaveBtnClicked(void)
{
    if (!xmlPath.isEmpty()) {
        this->saveData(xmlPath);
    }
}

void BillWidget::onCancelBtnClicked(void)
{
    this->close();
}
