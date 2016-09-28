#include "monthbillwidget.h"
#include "ui_monthbillwidget.h"

#include <QDate>
#include <QDebug>

//HTTP MonthBillWidget::http;

MonthBillWidget::MonthBillWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthBillWidget)
{
    ui->setupUi(this);
   // ui->yearLabel->setText(QDate::currentDate().toString("yyyy"));

    QSqlQuery query;
    //building
    query.exec("select building_id from building");
    ui->BuildingComboBox->addItem("全部");
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->BuildingComboBox->addItem(id);
    }
    ui->feeTypecomboBox->addItem("未交");
    ui->feeTypecomboBox->addItem("已交");
    ui->feeTypecomboBox->addItem("全部");
}

MonthBillWidget::~MonthBillWidget()
{
    delete ui;
}

void MonthBillWidget::on_selectPushButton_clicked()
{
    QSqlQuery query;
    QString start = ui->startDateEdit->text();
    QString stop = ui->stopdateEdit->text();
    qDebug()<<QString("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where payed=false and date >? and date <? ");
    if(ui->BuildingComboBox->currentText().compare("全部")==0)
    {
        if(ui->feeTypecomboBox->currentText().compare("未交")==0)
        {
            query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where payed=false and date >? and date <? ");
            query.addBindValue(start);
            query.addBindValue(stop);
        }
        else if(ui->feeTypecomboBox->currentText().compare("已交")==0)
        {
                query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where payed=true and date >? and date <? ");
                query.addBindValue(start);
                query.addBindValue(stop);
        }
        else if(ui->feeTypecomboBox->currentText().compare("全部")==0)
        {
                query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where date >? and date <? ");
                query.addBindValue(start);
                query.addBindValue(stop);
        }
    }
    else
    {
        if(ui->feeTypecomboBox->currentText().compare("未交")==0)
        {
            query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where payed=false and building_id=? and date >? and date <? ");
        }
        else if(ui->feeTypecomboBox->currentText().compare("已交")==0)
        {
             query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where payed=true and building_id=? and date >? and date <? ");
        }
        else if(ui->feeTypecomboBox->currentText().compare("全部")==0)
        {
             query.prepare("select id,name,building_id,room_id,date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor where building_id=? and date >? and date <? ");
        }
        query.addBindValue(ui->BuildingComboBox->currentText());
        query.addBindValue(start);
        query.addBindValue(stop);
    }
    query.exec();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(12);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("账单日期"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("水费"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("电费"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("天然气费"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("电视费用"));
    model->setHeaderData(9,Qt::Horizontal,QString::fromUtf8("物业费用"));
    model->setHeaderData(10,Qt::Horizontal,QString::fromUtf8("月房贷款"));
    model->setHeaderData(11,Qt::Horizontal,QString::fromUtf8("交费情况"));

    ui->tableView->model()->deleteLater();
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    while(query.next())
    {
        int i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString()));
        //设置字符颜色
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(query.value(1).toString()));
        model->setItem(i,2,new QStandardItem(query.value(2).toString()));
        model->setItem(i,3,new QStandardItem(query.value(3).toString()));
        model->setItem(i,4,new QStandardItem(query.value(4).toString()));
        model->setItem(i,5,new QStandardItem(query.value(5).toString()));
        model->setItem(i,6,new QStandardItem(query.value(6).toString()));
        model->setItem(i,7,new QStandardItem(query.value(7).toString()));
        model->setItem(i,8,new QStandardItem(query.value(8).toString()));
        model->setItem(i,9,new QStandardItem(query.value(9).toString()));
        model->setItem(i,10,new QStandardItem(query.value(10).toString()));
        if(query.value(11).toInt()==1)
        {
            model->setItem(i,11,new QStandardItem("已交"));
        }
        else
        {
            model->setItem(i,11,new QStandardItem("未交"));
        }
    }
}

/*

HTTP& MonthBillWidget::getHTTP()
{
    return MonthBillWidget::http;
}

*/
