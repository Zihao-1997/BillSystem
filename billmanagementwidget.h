#ifndef BILLMANAGEMENTMODEL_H
#define BILLMANAGEMENTMODEL_H

#include "billmodel.h"
#include "billwidget.h"
#include <QAbstractTableModel>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QList>
#include <QTableView>
#include <QDomDocument>
#include <QTextStream>
#include <QFile>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFileInfoList>

class BillManagementWidget : public QWidget
{
    Q_OBJECT

public:
    BillManagementWidget(QWidget *parent = nullptr);
    ~BillManagementWidget();

    void initUI(void);
    bool createXml(QString fileName, QString date);
    void showFileList(QTreeWidget *treeWidget, QFileInfoList infoList);
    void showFileList(QTreeWidgetItem *item, QFileInfoList infoList);
    void createEditBillWindow(void);

private:
    /* main window */
    QPushButton *createBillBtn;
    QPushButton *checkBillBtn;
    QPushButton *exportBillBtn;
    QVBoxLayout *mainLayout;

    /* create new bill window */
    QLabel *createBillLabel;
    QLabel *dateSelectLabel;
    QLabel *yearSelectLabel;
    QLabel *monthSelectLabel;
    QLabel *defaultRowsLabel;
    QComboBox *createBillBox;
    QComboBox *yearSelectBox;
    QComboBox *monthSelectBox;
    QPushButton *createBillConfirmBtn;
    QPushButton *createBillCancelBtn;
    QLineEdit *defaultRowsEdit;
    QGridLayout *selectBillTypeLayout;
    QWidget *selectBillTypeWindow;

    /* check bill window */
    QTreeWidget *checkBillWindow;

    QDomDocument xmlDoc;

private slots:
    void createBillBtnClicked(void);
    void createBillConfirmBtnClicked(void);
    void createBillCancelBtnClicked(void);
    void checkBillBtnClicked(void);
    void checkBillItemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    QString currentXmlPath;
    BillProcessModel *processModel;
    BillOutsoleModel *outsoleModel;
    QAbstractTableModel *model;
    BillWidget *billWidget;
};

#endif // BILLMANAGEMENTMODEL_H
