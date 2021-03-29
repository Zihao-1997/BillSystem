#ifndef BILLMODEL_H
#define BILLMODEL_H

#include <QString>
#include <QAbstractTableModel>
#include <QList>
#include <QDomDocument>
#include <QTextStream>
#include <QFile>

class BillProcessModel : public QAbstractTableModel
{   
    Q_OBJECT

public:
    explicit BillProcessModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void xmlWrite(QString fileName);
    bool xmlRead(QString fileName);
    void xmlClear(QString fileName);
    void xmlClearNodes(QDomNodeList &nodeList);
    void xmlCreateNodes(QDomElement &root);

public:
    typedef struct BillProcessFormat {
        QString date;
        QString name;
        QString model;
        QString item;
        QString method;
        uint32_t number;
        float price;
        uint32_t total;
    } BillProcessFormat;

    QList<BillProcessFormat> billProcessData;
    BillProcessFormat processDefaultData = { };
    QDomDocument doc;
};

class BillOutsoleModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BillOutsoleModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void xmlWrite(QString fileName);
    bool xmlRead(QString fileName);
    void xmlClear(QString fileName);
    void xmlClearNodes(QDomNodeList &nodeList);
    void xmlCreateNodes(QDomElement &root);

public:
    typedef struct BillOutsoleFormat {
        QString date;
        QString name;
        QString model;
        QString color;
        uint32_t number;
        float price;
        uint32_t total;
    } BillOutsoleFormat;

    QList<BillOutsoleFormat> billOutsoleData;
    BillOutsoleFormat outsoleDefaultData = { };
    QDomDocument doc;
};


#endif // BILLMODEL_H
