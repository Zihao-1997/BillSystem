#ifndef CLIENTINFOMODEL_H
#define CLIENTINFOMODEL_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QTableView>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


enum ProductType {
    typeA = 0x01,
    typeB,
    typeC
};

typedef struct ClientInfo {
    QString clientName;
    ProductType productType;
    QString address;
    QString contact;
    QString phoneNumber;
} ClientInfo;

class ClientInfoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ClientInfoModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

public:
    QString getProductType(ProductType type) const;

private:
    QList<ClientInfo> clienInfoData;
//    ClientInfo defaultData = {"ZhangSan", typeA, "address", "ZhangSan", "123"};
    ClientInfo defaultData = { };

};

class ClientInfoWidget : public QWidget
{
    Q_OBJECT

public:
    ClientInfoWidget(QWidget *parent = nullptr);
    ~ClientInfoWidget();

private:
    void initUI(void);

private:
    QPushButton *addRowBtn;
    QPushButton *deleteRowBtn;
    QHBoxLayout *upperLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *mainLayout;

    ClientInfoModel *clientInfoModel;
    QTableView *clientInfoTableView;

private slots:
    void addRowButtonClicked(void);
    void deleteRowButtonClicked(void);
};

#endif // CLIENTINFOMODEL_H
