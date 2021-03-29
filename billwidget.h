#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QAbstractTableModel>
#include "billmodel.h"

class BillWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BillWidget(QWidget *parent = nullptr, QAbstractTableModel *model = nullptr);
    ~BillWidget();

    void addRows(int row, int count);
    void deleteRows(int row, int count);
    bool readData(QString fileName);
    void saveData(QString fileName);
    void setXmlPath(QString path);

private:
    void initUI(void);

signals:

private slots:
    void onAddBtnClicked(void);
    void onDeleteBtnClicked(void);
    void onSaveBtnClicked(void);
    void onCancelBtnClicked(void);

private:
    QPushButton *addRowBtn;
    QPushButton *deleteRowBtn;
    QPushButton *saveBillBtn;
    QPushButton *cancelEditBtn;
    QHBoxLayout *upperLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *mainLayout;
    QAbstractTableModel *billModel;
    QTableView *billView;

    QString xmlPath;
};

#endif // BILLWIDGET_H
