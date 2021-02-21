#include "billmanagementwidget.h"
#include <QItemSelectionModel>

BillManagementModel::BillManagementModel(QObject *parent, BillType type)
    : QAbstractTableModel(parent), billType(type)
{
}

QVariant BillManagementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (billType == BILL_TYPE_PROCESS) {
                switch (section) {
                case 0: return QString("Date");
                case 1: return QString("Name");
                case 2: return QString("Model");
                case 3: return QString("Item");
                case 4: return QString("Method");
                case 5: return QString("Number");
                case 6: return QString("Price");
                case 7: return QString("Total");
                }
            }
            else if (billType == BILL_TYPE_OUTSOLE) {
                switch (section) {
                case 0: return QString("Date");
                case 1: return QString("Name");
                case 2: return QString("Model");
                case 3: return QString("Color");
                case 4: return QString("Number");
                case 5: return QString("Price");
                case 6: return QString("Total");
                }
            }
        }
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignHCenter;
        }
    }

    return QVariant();
}

//bool BillManagementModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


int BillManagementModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (billType == BILL_TYPE_PROCESS) {
        return billProcessData.count();
    }
    else if (billType == BILL_TYPE_OUTSOLE) {
        return billOutsoleData.count();
    }

    return 0;
}

int BillManagementModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (billType == BILL_TYPE_PROCESS) {
        return 8;
    }
    else if (billType == BILL_TYPE_OUTSOLE) {
        return 7;
    }

    return 0;
}

QVariant BillManagementModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const int row = index.row();
        const int column = index.column();
        if (billType == BILL_TYPE_PROCESS) {
            switch (column) {
            case 0: return billProcessData[row].date;
            case 1: return billProcessData[row].name;
            case 2: return billProcessData[row].model;
            case 3: return billProcessData[row].item;
            case 4: return billProcessData[row].method;
            case 5: return billProcessData[row].number;
            case 6: return billProcessData[row].price;
            case 7: return billProcessData[row].total;
            }
        }
        else if (billType == BILL_TYPE_OUTSOLE) {
            switch (column) {
            case 0: return billOutsoleData[row].date;
            case 1: return billOutsoleData[row].name;
            case 2: return billOutsoleData[row].model;
            case 3: return billOutsoleData[row].color;
            case 4: return billOutsoleData[row].number;
            case 5: return billOutsoleData[row].price;
            case 6: return billOutsoleData[row].total;
            }
        }
    }

    return QVariant();
}

bool BillManagementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        const int row = index.row();
        const int column = index.column();
        if (billType == BILL_TYPE_PROCESS) {
            switch (column) {
            case 0: billProcessData[row].date = value.toString();   break;
            case 1: billProcessData[row].name = value.toString();   break;
            case 2: billProcessData[row].model = value.toString();  break;
            case 3: billProcessData[row].item = value.toString();   break;
            case 4: billProcessData[row].method = value.toString(); break;
            case 5: billProcessData[row].number = value.toUInt();   break;
            case 6: billProcessData[row].price = value.toFloat();   break;
            case 7: billProcessData[row].total = value.toUInt();    break;
            }
        }
        else if (billType == BILL_TYPE_OUTSOLE) {
            switch (column) {
            case 0: billOutsoleData[row].date = value.toString();   break;
            case 1: billOutsoleData[row].name = value.toString();   break;
            case 2: billOutsoleData[row].model = value.toString();  break;
            case 3: billOutsoleData[row].color = value.toString();  break;
            case 4: billOutsoleData[row].number = value.toUInt();   break;
            case 5: billOutsoleData[row].price = value.toFloat();   break;
            case 6: billOutsoleData[row].total = value.toUInt();    break;
            }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags BillManagementModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool BillManagementModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    if (billType == BILL_TYPE_PROCESS) {
        for (int i = row; i < row+count; i++) {
            billProcessData.insert(i, processDefaultData);
        }
    }
    else if (billType == BILL_TYPE_OUTSOLE) {
        for (int i = row; i < row+count; i++) {
            billOutsoleData.insert(i, outsoleDefaultData);
        }
    }
    endInsertRows();

    return true;
}

//bool BillManagementModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//}

bool BillManagementModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    if (billType == BILL_TYPE_PROCESS) {
        for (int i = row+count-1; i > row; i--) {
            billProcessData.removeAt(i);
        }
    }
    else if (billType == BILL_TYPE_OUTSOLE) {
        for (int i = row+count-1; i > row; i--) {
            billOutsoleData.removeAt(i);
        }
    }
    endRemoveRows();

    return true;
}

//bool BillManagementModel::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//}

BillManagementWidget::BillManagementWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

BillManagementWidget::~BillManagementWidget()
{

}

void BillManagementWidget::initUI()
{
    createBillBtn = new QPushButton("CreateBill");
    checkBillBtn = new QPushButton("CheckBill");
    exportBillBtn = new QPushButton("ExportBill");

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createBillBtn);
    mainLayout->addWidget(checkBillBtn);
    mainLayout->addWidget(exportBillBtn);

    connect(createBillBtn, &QPushButton::clicked, this, &BillManagementWidget::createBillBtnClicked);
}

void BillManagementWidget::createBillBtnClicked(void)
{
    createBillLabel = new QLabel("Select Type");
    createBillBox = new QComboBox();
    createBillBox->addItem("Process");
    createBillBox->addItem("Outsole");
    createBillConfirmBtn = new QPushButton("Confirm");
    createBillCancelBtn = new QPushButton("Cancel");

    selectBillTypeLayout = new QGridLayout();
    selectBillTypeLayout->addWidget(createBillLabel, 0, 0, 1, 2);
    selectBillTypeLayout->addWidget(createBillBox, 0, 2, 1, 2);
    selectBillTypeLayout->addWidget(createBillConfirmBtn, 1, 2, 1, 1);
    selectBillTypeLayout->addWidget(createBillCancelBtn, 1, 3, 1, 1);

    selectBillTypeWindow = new QWidget();
    selectBillTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
    selectBillTypeWindow->setLayout(selectBillTypeLayout);
    selectBillTypeWindow->show();

    connect(createBillConfirmBtn, &QPushButton::clicked, this, &BillManagementWidget::createBillConfirmBtnClicked);
}

void BillManagementWidget::createBillConfirmBtnClicked(void)
{
    newBillView = new QTableView();
    if (createBillBox->currentText().compare("Process") == 0) {
        newBillModel = new BillManagementModel(nullptr, BILL_TYPE_PROCESS);
    }
    else {
        newBillModel = new BillManagementModel(nullptr, BILL_TYPE_OUTSOLE);
    }

    newBillView->setModel(newBillModel);

    addRowBtn = new QPushButton("Add");
    deleteRowBtn = new QPushButton("Delete");
    upperLayout = new QHBoxLayout();
    upperLayout->addWidget(addRowBtn);
    upperLayout->addWidget(deleteRowBtn);
    bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(newBillView);
    newBillLayout = new QVBoxLayout();
    newBillLayout->addLayout(upperLayout);
    newBillLayout->addLayout(bottomLayout);
    newBillWindow = new QWidget();
    newBillWindow->setLayout(newBillLayout);
    newBillWindow->show();
    selectBillTypeWindow->close();

    connect(addRowBtn, &QPushButton::clicked, this, &BillManagementWidget::newBillAddRowBtnClicked);
    connect(deleteRowBtn, &QPushButton::clicked, this, &BillManagementWidget::newBillDeleteRowBtnClicked);
}

void BillManagementWidget::createBillCancelBtnClicked(void)
{

}

void BillManagementWidget::newBillAddRowBtnClicked(void)
{
    QItemSelectionModel *selectionModel = newBillView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("add row = %d, column = %d", index.row(), index.column());
    newBillModel->insertRow(index.row()+1);
}

void BillManagementWidget::newBillDeleteRowBtnClicked(void)
{
    QItemSelectionModel *selectionModel = newBillView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("delete row = %d, column = %d", index.row(), index.column());
    newBillModel->removeRow(index.row());
}
