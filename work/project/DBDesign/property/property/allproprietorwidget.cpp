#include "allproprietorwidget.h"
#include "ui_allproprietorwidget.h"

#include <QSqlQuery>
#include <QStandardItemModel>
#include <QByteArray>
#include <QDebug>

HTTP AllProprietorWidget::http;

AllProprietorWidget::AllProprietorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllProprietorWidget)
{
    ui->setupUi(this);
    QSqlQuery query;
    //building comobox
    query.exec("select building_id from building");
    ui->comboBox->addItem("全部");

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->comboBox->addItem(id);
    }

    query.exec("select * from proprietor left  outer join proprietor_phone_num on proprietor.ID = proprietor_phone_num.ID");

    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("手机号码"));
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    int rowNum=0;
    while(query.next())
    {
        rowNum = model->rowCount();
        model->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        QByteArray b = query.value(1).toByteArray();
        model->setItem(rowNum,1,new QStandardItem(QString::fromLatin1(b) ));
        model->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        model->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        model->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        model->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
        model->setItem(rowNum,6,new QStandardItem(query.value(6).toString() ));
    }
}

AllProprietorWidget::~AllProprietorWidget()
{
    ui->tableView->model()->deleteLater();
    delete ui;
}

void AllProprietorWidget::on_comboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    QSqlQuery query;
    if(ui->comboBox->currentText().compare("全部") == 0)
    {
        query.exec("select * from proprietor left  outer join proprietor_phone_num on proprietor.ID = proprietor_phone_num.ID");
    }
    else
    {
        query.exec(QString("select * from proprietor left  outer join proprietor_phone_num on proprietor.ID = proprietor_phone_num.ID where building_id=%1").arg(ui->comboBox->currentText()));
    }

    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("手机号码"));
    ui->tableView->model()->deleteLater();
    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    int rowNum=0;
    while(query.next())
    {
        rowNum = model->rowCount();
        model->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        model->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        model->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        model->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
        model->setItem(rowNum,6,new QStandardItem(query.value(6).toString() ));
    }
}

HTTP& AllProprietorWidget::getHTTP()
{
    return AllProprietorWidget::http;
}
