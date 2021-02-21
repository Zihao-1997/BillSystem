#include "clientinfomodel.h"
#include <QItemSelectionModel>
#include <QDebug>

ClientInfoModel::ClientInfoModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    clienInfoData = QList<ClientInfo>{
        {"ZhangSan", typeA, "addressA", "ZhangSan", "123"},
        {"LiSi", typeB, "addressB", "LiSi", "456"}
    };
}

QVariant ClientInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case 0:
                return QString("ClientName");

            case 1:
                return QString("ProductType");

            case 2:
                return QString("Address");

            case 3:
                return QString("Contact");

            case 4:
                return QString("PhoneNumber");
            }
        }
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignHCenter;
        }
    }

    return QVariant();
}

//bool ClientInfoModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


int ClientInfoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return clienInfoData.count();
}

int ClientInfoModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant ClientInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const int row = index.row();
        const int column = index.column();
        switch (column) {
        case 0:
            return clienInfoData.at(row).clientName;

        case 1:
            return getProductType(clienInfoData.at(row).productType);

        case 2:
            return clienInfoData.at(row).address;

        case 3:
            return clienInfoData.at(row).contact;

        case 4:
            return clienInfoData.at(row).phoneNumber;
        }
    }

    return QVariant();
}

bool ClientInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        const int row = index.row();
        const int column = index.column();
        switch (column) {
        case 0:
            clienInfoData[row].clientName = value.toString();
            break;

        case 1:
            clienInfoData[row].productType = ProductType(value.toInt());
            break;

        case 2:
            clienInfoData[row].address = value.toString();
            break;

        case 3:
            clienInfoData[row].contact = value.toString();
            break;

        case 4:
            clienInfoData[row].phoneNumber = value.toString();
            break;
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ClientInfoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool ClientInfoModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i < row+count; i++) {
        clienInfoData.insert(i, defaultData);
    }
    endInsertRows();
    return true;
}

//bool ClientInfoModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//}

bool ClientInfoModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row+count-1; i >= row; i--) {
        clienInfoData.removeAt(i);
    }
    endRemoveRows();
    return true;
}

//bool ClientInfoModel::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//}

QString ClientInfoModel::getProductType(ProductType type) const
{
    switch (type) {
    case typeA:
        return QString("typeA");
        break;

    case typeB:
        return QString("typeB");
        break;

    case typeC:
        return QString("typeC");
        break;

    default:
        return QString("");
        break;
    }
}

ClientInfoWidget::ClientInfoWidget(QWidget *parent)
    :QWidget(parent)
{
    initUI();
}

ClientInfoWidget::~ClientInfoWidget()
{

}

void ClientInfoWidget::initUI(void)
{
    clientInfoTableView = new QTableView();
    clientInfoModel = new ClientInfoModel();
    clientInfoTableView->setModel(clientInfoModel);

    addRowBtn = new QPushButton("Add");
    deleteRowBtn = new QPushButton("Delete");

    upperLayout = new QHBoxLayout();
    upperLayout->addWidget(addRowBtn);
    upperLayout->addWidget(deleteRowBtn);
    bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(clientInfoTableView);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(bottomLayout);

    connect(addRowBtn, &QPushButton::clicked, this, &ClientInfoWidget::addRowButtonClicked);
    connect(deleteRowBtn, &QPushButton::clicked, this, &ClientInfoWidget::deleteRowButtonClicked);
}

void ClientInfoWidget::addRowButtonClicked(void)
{
    QItemSelectionModel *selectionModel = clientInfoTableView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("add row = %d, column = %d", index.row(), index.column());

    if (clientInfoModel != nullptr) {
        clientInfoModel->insertRow(index.row()+1);
    }
}

void ClientInfoWidget::deleteRowButtonClicked(void)
{
    QItemSelectionModel *selectionModel = clientInfoTableView->selectionModel();
    QModelIndex index = selectionModel->currentIndex();
    qDebug("delete row = %d, column = %d", index.row(), index.column());

    if (clientInfoModel != nullptr) {
        clientInfoModel->removeRow(index.row());
    }
}
