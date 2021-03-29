#include "billmodel.h"
#include <QDebug>

BillProcessModel::BillProcessModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QVariant BillProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
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
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignHCenter;
        }
    }

    return QVariant();
}

int BillProcessModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return billProcessData.count();
}

int BillProcessModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 8;
}

QVariant BillProcessModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const int row = index.row();
        const int column = index.column();
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

    return QVariant();
}

bool BillProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        const int row = index.row();
        const int column = index.column();
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
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags BillProcessModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool BillProcessModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count < 1 || row > rowCount()) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i < row+count; i++) {
        billProcessData.insert(i, processDefaultData);
    }
    endInsertRows();

    return true;
}

bool BillProcessModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count < 1 || row+count > rowCount()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row+count-1; i >= row; i--) {
        billProcessData.removeAt(i);
    }
    endRemoveRows();

    return true;
}

void BillProcessModel::xmlWrite(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return ;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }
    QDomElement root = doc.documentElement();
    xmlCreateNodes(root);
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

bool BillProcessModel::xmlRead(QString fileName)
{
    QFile file(fileName);
    qDebug() << "file = " << fileName;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return false;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return false;
    }

    BillProcessFormat processData;
    QDomElement root = doc.documentElement();
    QDomNodeList rootNodeList = root.childNodes();
    for (int i = 0; i < rootNodeList.count(); i++) {
        processData.date = rootNodeList.at(i).toElement().attribute("day");
        QDomNodeList childNodeList = rootNodeList.at(i).childNodes();
        processData.name = childNodeList.at(0).toElement().text();
        processData.model = childNodeList.at(1).toElement().text();
        processData.item = childNodeList.at(2).toElement().text();
        processData.method = childNodeList.at(3).toElement().text();
        processData.number = childNodeList.at(4).toElement().text().toUInt();
        processData.price = childNodeList.at(5).toElement().text().toFloat();
        processData.total = childNodeList.at(6).toElement().text().toUInt();
        billProcessData.append(processData);
    }

    return true;
}

void BillProcessModel::xmlClear(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return ;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }
    QDomElement root = doc.documentElement();
    QDomNodeList list = root.childNodes();
    xmlClearNodes(list);
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

void BillProcessModel::xmlClearNodes(QDomNodeList &nodeList)
{
    while (!nodeList.isEmpty()) {
        QDomNode node = nodeList.at(0);
        if (node.hasChildNodes()) {
            QDomNodeList list = node.childNodes();
            xmlClearNodes(list);
        }
        node.parentNode().removeChild(node);
    }
}

void BillProcessModel::xmlCreateNodes(QDomElement &root)
{
    QDomElement name;
    QDomElement model;
    QDomElement item;
    QDomElement method;
    QDomElement number;
    QDomElement price;
    QDomElement total;
    QDomElement date;
    QDomAttr dayAttr;
    QDomText text;

    for (int i = 0; i < billProcessData.size(); i++) {
        date =doc.createElement("date");
        dayAttr = doc.createAttribute("day");
        dayAttr.setValue(billProcessData[i].date);
        date.setAttributeNode(dayAttr);
        text = doc.createTextNode(billProcessData[i].name);
        name = doc.createElement(QString("name"));
        name.appendChild(text);
        date.appendChild(name);
        text = doc.createTextNode(billProcessData[i].model);
        model = doc.createElement(QString("model"));
        model.appendChild(text);
        date.appendChild(model);
        text = doc.createTextNode(billProcessData[i].item);
        item = doc.createElement(QString("item"));
        item.appendChild(text);
        date.appendChild(item);
        text = doc.createTextNode(billProcessData[i].method);
        method = doc.createElement(QString("method"));
        method.appendChild(text);
        date.appendChild(method);
        text = doc.createTextNode(QString("%1").arg(billProcessData[i].number));
        number = doc.createElement(QString("number"));
        number.appendChild(text);
        date.appendChild(number);
        text = doc.createTextNode(QString("%1").arg(billProcessData[i].price));
        price = doc.createElement(QString("pricec"));
        price.appendChild(text);
        date.appendChild(price);
        text = doc.createTextNode(QString("%1").arg(billProcessData[i].total));
        total = doc.createElement(QString("total"));
        total.appendChild(text);
        date.appendChild(total);
        root.appendChild(date);
    }
}

BillOutsoleModel::BillOutsoleModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QVariant BillOutsoleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
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
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignHCenter;
        }
    }

    return QVariant();
}

int BillOutsoleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return billOutsoleData.count();
}

int BillOutsoleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

   return 7;
}

QVariant BillOutsoleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const int row = index.row();
        const int column = index.column();
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

    return QVariant();
}

bool BillOutsoleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        const int row = index.row();
        const int column = index.column();
        switch (column) {
        case 0: billOutsoleData[row].date = value.toString();   break;
        case 1: billOutsoleData[row].name = value.toString();   break;
        case 2: billOutsoleData[row].model = value.toString();  break;
        case 3: billOutsoleData[row].color = value.toString();  break;
        case 4: billOutsoleData[row].number = value.toUInt();   break;
        case 5: billOutsoleData[row].price = value.toFloat();   break;
        case 6: billOutsoleData[row].total = value.toUInt();    break;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags BillOutsoleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool BillOutsoleModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count < 1 || row > rowCount()) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i < row+count; i++) {
        billOutsoleData.insert(i, outsoleDefaultData);
    }
    endInsertRows();

    return true;
}

bool BillOutsoleModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count < 1 || row+count > rowCount()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row+count-1; i >= row; i--) {
        billOutsoleData.removeAt(i);
    }
    endRemoveRows();

    return true;
}

void BillOutsoleModel::xmlWrite(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return ;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }

    QDomElement root = doc.documentElement();
    xmlCreateNodes(root);
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

bool BillOutsoleModel::xmlRead(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return false;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return false;
    }

    BillOutsoleFormat outsoleData;
    QDomElement root = doc.documentElement();
    QDomNodeList rootNodeList = root.childNodes();
    for (int i = 0; i < rootNodeList.count(); i++) {
        outsoleData.date = rootNodeList.at(i).toElement().attribute("day");
        QDomNodeList childNodeList = rootNodeList.at(i).childNodes();
        outsoleData.name = childNodeList.at(0).toElement().text();
        outsoleData.model = childNodeList.at(1).toElement().text();
        outsoleData.color = childNodeList.at(2).toElement().text();
        outsoleData.number = childNodeList.at(3).toElement().text().toUInt();
        outsoleData.price = childNodeList.at(4).toElement().text().toFloat();
        outsoleData.total = childNodeList.at(5).toElement().text().toUInt();
        billOutsoleData.append(outsoleData);
    }

    return true;
}

void BillOutsoleModel::xmlClear(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "doc set content failed.";
        file.close();
        return ;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "open " + fileName + " failed.";
        return ;
    }
    QDomElement root = doc.documentElement();
    QDomNodeList list = root.childNodes();
    xmlClearNodes(list);
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
}

void BillOutsoleModel::xmlClearNodes(QDomNodeList &nodeList)
{
    while (!nodeList.isEmpty()) {
        QDomNode node = nodeList.at(0);
        if (node.hasChildNodes()) {
            QDomNodeList list = node.childNodes();
            xmlClearNodes(list);
        }
        node.parentNode().removeChild(node);
    }
}

void BillOutsoleModel::xmlCreateNodes(QDomElement &root)
{
    QDomElement name;
    QDomElement model;
    QDomElement color;
    QDomElement number;
    QDomElement price;
    QDomElement total;
    QDomElement date;
    QDomAttr dayAttr;
    QDomText text;

    for (int i = 0; i < billOutsoleData.size(); i++) {
        date =doc.createElement("date");
        dayAttr = doc.createAttribute("day");
        dayAttr.setValue(billOutsoleData[i].date);
        date.setAttributeNode(dayAttr);
        text = doc.createTextNode(billOutsoleData[i].name);
        name = doc.createElement(QString("name"));
        name.appendChild(text);
        date.appendChild(name);
        text = doc.createTextNode(billOutsoleData[i].model);
        model = doc.createElement(QString("model"));
        model.appendChild(text);
        date.appendChild(model);
        text = doc.createTextNode(billOutsoleData[i].color);
        color = doc.createElement(QString("color"));
        color.appendChild(text);
        date.appendChild(color);
        text = doc.createTextNode(QString("%1").arg(billOutsoleData[i].number));
        number = doc.createElement(QString("number"));
        number.appendChild(text);
        date.appendChild(number);
        text = doc.createTextNode(QString("%1").arg(billOutsoleData[i].price));
        price = doc.createElement(QString("pricec"));
        price.appendChild(text);
        date.appendChild(price);
        text = doc.createTextNode(QString("%1").arg(billOutsoleData[i].total));
        total = doc.createElement(QString("total"));
        total.appendChild(text);
        date.appendChild(total);
        root.appendChild(date);
    }
}
