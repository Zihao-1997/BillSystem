#include "billmanagementwidget.h"
#include "billmodel.h"
#include "billwidget.h"
#include <QItemSelectionModel>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QIcon>

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
    connect(checkBillBtn, &QPushButton::clicked, this, &BillManagementWidget::checkBillBtnClicked);
}

bool BillManagementWidget::createXml(QString fileName, QString date)
{
    QFile file(fileName);

    if (file.exists())
        return true;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    QDomElement root;
    QDomAttr rootAttr;
    QTextStream out(&file);
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    root = doc.createElement(QString("Bill"));
    rootAttr = doc.createAttribute(QString("month"));
    rootAttr.setValue(date);
    root.setAttributeNode(rootAttr);
    doc.appendChild(root);
    doc.save(out, QDomNode::EncodingFromDocument);
    file.close();

    return true;
}


void BillManagementWidget::showFileList(QTreeWidget *treeWidget, QFileInfoList infoList)
{
    QFileInfo info;
    QDir dir;
    QFileInfoList list;

    for (int i = 0; i < infoList.size(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        info = infoList.at(i);
        if (info.fileName() == "." || info.fileName() == "..") {
            continue;
        }

        if (info.isDir()) {
            item->setText(0, info.fileName());
            item->setIcon(0, QIcon("://image/icon/dir.png"));
            treeWidget->addTopLevelItem(item);
            dir.setPath(info.filePath());
            dir.setFilter(QDir::Files | QDir::Dirs);
            dir.setSorting(QDir::DirsFirst);
            list = dir.entryInfoList();
            showFileList(item, list);
        }
        else if (info.isFile()) {
            item->setText(0, info.fileName());
            item->setIcon(0, QIcon("://image/icon/XML.png"));
            treeWidget->addTopLevelItem(item);
        }
    }
}

void BillManagementWidget::showFileList(QTreeWidgetItem *item, QFileInfoList infoList)
{
    QFileInfo info;
    QDir dir;
    QFileInfoList list;

    for (int i = 0; i < infoList.size(); i++) {
        QTreeWidgetItem *childItem = new QTreeWidgetItem();
        info = infoList.at(i);
        if (info.fileName() == "." || info.fileName() == "..") {
            continue;
        }

        if (info.isDir()) {
            childItem->setText(0, info.fileName());
            childItem->setIcon(0, QIcon("://image/icon/dir.png"));
            item->addChild(childItem);
            dir.setPath(info.filePath());
            dir.setFilter(QDir::Files | QDir::Dirs);
            dir.setSorting(QDir::DirsFirst);
            list = dir.entryInfoList();
            showFileList(childItem, list);
        }
        else if (info.isFile()) {
            childItem->setText(0, info.fileName());
            childItem->setIcon(0, QIcon("://image/icon/XML.png"));
            item->addChild(childItem);
        }
    }
}

void BillManagementWidget::createBillBtnClicked(void)
{
    createBillLabel = new QLabel("Select Type");
    dateSelectLabel = new QLabel("Select Date");
    yearSelectLabel = new QLabel("year");\
    yearSelectLabel->setAlignment(Qt::AlignCenter);
    monthSelectLabel = new QLabel("month");
    monthSelectLabel->setAlignment(Qt::AlignCenter);
    defaultRowsLabel = new QLabel("Default Rows");

    createBillBox = new QComboBox();
    createBillBox->addItem("Process");
    createBillBox->addItem("Outsole");

    yearSelectBox = new QComboBox();
    for (int i = 2010; i <= 2030; i++) {
        yearSelectBox->addItem(QString("%1").arg(i));
    }
    yearSelectBox->setCurrentText(QString("2021"));

    monthSelectBox = new QComboBox();
    for (int i = 1; i <= 12; i++) {
        monthSelectBox->addItem(QString("%1").arg(i));
    }

    defaultRowsEdit = new QLineEdit(QString("1"));

    createBillConfirmBtn = new QPushButton("Confirm");
    createBillCancelBtn = new QPushButton("Cancel");

    selectBillTypeLayout = new QGridLayout();
    selectBillTypeLayout->addWidget(createBillLabel, 0, 0, 1, 1);
    selectBillTypeLayout->addWidget(createBillBox, 0, 1, 1, 2);
    selectBillTypeLayout->addWidget(dateSelectLabel, 1, 0, 1, 1);
    selectBillTypeLayout->addWidget(yearSelectLabel, 1, 1, 1, 1);
    selectBillTypeLayout->addWidget(yearSelectBox, 1, 2, 1, 1);
    selectBillTypeLayout->addWidget(monthSelectLabel, 1, 3, 1, 1);
    selectBillTypeLayout->addWidget(monthSelectBox, 1, 4, 1, 1);
    selectBillTypeLayout->addWidget(defaultRowsLabel, 2, 0, 1, 1);
    selectBillTypeLayout->addWidget(defaultRowsEdit, 2, 1, 1, 2);
    selectBillTypeLayout->addWidget(createBillConfirmBtn, 3, 3, 1, 1);
    selectBillTypeLayout->addWidget(createBillCancelBtn, 3, 4, 1, 1);

    selectBillTypeWindow = new QWidget();
    selectBillTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
    selectBillTypeWindow->setLayout(selectBillTypeLayout);
    selectBillTypeWindow->show();

    connect(createBillConfirmBtn, &QPushButton::clicked, this, &BillManagementWidget::createBillConfirmBtnClicked);
}

void BillManagementWidget::createBillConfirmBtnClicked(void)
{
    QDir dir;
    QString billDir = QString("./data/%1/%2/").arg(yearSelectBox->currentText()).arg(monthSelectBox->currentText());
    if (!dir.exists(billDir)) {
        dir.mkpath(billDir);
        qDebug() << "create bill month directory";
    }

    QString date = QString("%1-%2").arg(yearSelectBox->currentText()).arg(monthSelectBox->currentText(), 2, '0');
    QString fileName = QString("%1-%2%3.xml").arg(createBillBox->currentText()).arg(yearSelectBox->currentText()).
            arg(monthSelectBox->currentText(), 2, '0');
    currentXmlPath = billDir + fileName;
    QFile file(currentXmlPath);

    if (createBillBox->currentText().compare("Process") == 0) {
        model = new BillProcessModel();
        billWidget = new BillWidget(nullptr, model);
        if (file.exists()) {
            qDebug() << "read data";
            billWidget->readData(currentXmlPath);
        }
        else {
            if (!createXml(currentXmlPath, date)) {
                qDebug() << "create xml failed.";
            }
            model->insertRows(0, defaultRowsEdit->text().toInt());
        }
        billWidget->setXmlPath(currentXmlPath);
        billWidget->resize(1000, 400);
        billWidget->show();
    }
    else {
        model = new BillOutsoleModel();
        billWidget = new BillWidget(nullptr, model);
        if (file.exists()) {
            qDebug() << "read data";
            billWidget->readData(currentXmlPath);
        }
        else {
            if (!createXml(currentXmlPath, date)) {
                qDebug() << "create xml failed.";
            }
            model->insertRows(0, defaultRowsEdit->text().toInt());
        }
        billWidget->setXmlPath(currentXmlPath);
        billWidget->resize(1000, 400);
        billWidget->show();
    }

    selectBillTypeWindow->close();
}

void BillManagementWidget::createBillCancelBtnClicked(void)
{

}

void BillManagementWidget::checkBillBtnClicked(void)
{
    checkBillWindow = new QTreeWidget();

    QDir rootDir("./data");
    if (!rootDir.exists()) {
        delete  checkBillWindow;
        return ;
    }

    rootDir.setFilter(QDir::Dirs | QDir::Files);
    rootDir.setSorting(QDir::DirsFirst);
    QFileInfoList infoList = rootDir.entryInfoList();
    showFileList(checkBillWindow, infoList);

    connect(checkBillWindow, &QTreeWidget::itemDoubleClicked, this, &BillManagementWidget::checkBillItemDoubleClicked);

    checkBillWindow->expandAll();
    checkBillWindow->setExpandsOnDoubleClick(false);
    checkBillWindow->resize(400, 400);
    checkBillWindow->show();
}

void BillManagementWidget::checkBillItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString filePath = item->text(column);
    QString xmlFile;

    if (item->text(column).contains("Process")) {
        model = new BillProcessModel();
    }
    else if (item->text(column).contains("Outsole")) {
        model = new BillOutsoleModel();
    }

    QTreeWidgetItem *itemParent = item->parent();
    while (itemParent != nullptr) {
        filePath = itemParent->text(column) + '/' + filePath;
        itemParent = itemParent->parent();
    }
    filePath = "./data/" + filePath;
    qDebug() << "file path: " + filePath;

    billWidget = new BillWidget(nullptr, model);
    billWidget->readData(filePath);
    billWidget->resize(1000, 400);
    billWidget->show();
}
