#ifndef BILLMANAGEMENTMODEL_H
#define BILLMANAGEMENTMODEL_H

#include <QAbstractTableModel>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QList>
#include <QTableView>

enum BillType {
    BILL_TYPE_PROCESS = 0x01,
    BILL_TYPE_OUTSOLE
};

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

typedef struct BillOutsoleFormat {
    QString date;
    QString name;
    QString model;
    QString color;
    uint32_t number;
    float price;
    uint32_t total;
} BillOutsoleFormat;

class BillManagementModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BillManagementModel(QObject *parent = nullptr, BillType type = BILL_TYPE_OUTSOLE);

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

private:
    BillType billType;
    QList<BillProcessFormat> billProcessData;
    QList<BillOutsoleFormat> billOutsoleData;
    BillProcessFormat processDefaultData = { };
    BillOutsoleFormat outsoleDefaultData = { };
};

class BillManagementWidget : public QWidget
{
    Q_OBJECT

public:
    BillManagementWidget(QWidget *parent = nullptr);
    ~BillManagementWidget();

    void initUI(void);

private:
    /* main window */
    QPushButton *createBillBtn;
    QPushButton *checkBillBtn;
    QPushButton *exportBillBtn;
    QVBoxLayout *mainLayout;

    /* create new bill window */
    QLabel *createBillLabel;
    QComboBox *createBillBox;
    QPushButton *createBillConfirmBtn;
    QPushButton *createBillCancelBtn;
    QGridLayout *selectBillTypeLayout;
    QWidget *selectBillTypeWindow;

    /* new bill window */
    QPushButton *addRowBtn;
    QPushButton *deleteRowBtn;
    QHBoxLayout *upperLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *newBillLayout;
    QWidget *newBillWindow;
    QTableView *newBillView;
    BillManagementModel *newBillModel;

private slots:
    void createBillBtnClicked(void);
    void createBillConfirmBtnClicked(void);
    void createBillCancelBtnClicked(void);
    void newBillAddRowBtnClicked(void);
    void newBillDeleteRowBtnClicked(void);
};

#endif // BILLMANAGEMENTMODEL_H
