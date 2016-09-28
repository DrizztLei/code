#include "monthbillreportwidget.h"
#include "ui_monthbillreportwidget.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QStandardItemModel>
MonthBillReportWidget::MonthBillReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthBillReportWidget)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("select min(date) min_date,max(date) max_date from month_bill");
    int begin_year;
    int end_year;
    while(query.next()){
        begin_year = query.value(0).toDate().toString("yyyy").toInt();
        end_year = query.value(1).toDate().toString("yyyy").toInt();
    }
    while(begin_year<=end_year){
        ui->yearomboBox->addItem(QString("%1").arg(begin_year));
         begin_year++;
    }
    ui->monthComboBox->addItem("01");
    ui->monthComboBox->addItem("02");
    ui->monthComboBox->addItem("03");
    ui->monthComboBox->addItem("04");
    ui->monthComboBox->addItem("05");
    ui->monthComboBox->addItem("06");
    ui->monthComboBox->addItem("07");
    ui->monthComboBox->addItem("08");
    ui->monthComboBox->addItem("09");
    ui->monthComboBox->addItem("10");
    ui->monthComboBox->addItem("11");
    ui->monthComboBox->addItem("12");

    ui->feeTypeComboBox->addItem("应收未收");
    ui->feeTypeComboBox->addItem("实收费用");
    ui->feeTypeComboBox->addItem("应收费用");
}

MonthBillReportWidget::~MonthBillReportWidget()
{
    delete ui;
}

void MonthBillReportWidget::on_selectPushButton_clicked()
{
    QSqlQuery query;
    QString y = ui->yearomboBox->currentText();
    QString m = ui->monthComboBox->currentText();
    if(ui->feeTypeComboBox->currentText().compare("应收未收") == 0){
        query.prepare(QString("select id, name, building_id, room_id, date, water, watt, gas, tv, property, mortage,payed from proprietor natural join month_bill where payed=false and date like '%1-%2-%'").arg(y).arg(m));
    }else if(ui->feeTypeComboBox->currentText().compare("实收费用") == 0){
        query.prepare(QString("select id, name, building_id, room_id, date, water, watt, gas, tv, property, mortage,payed from proprietor natural join month_bill where payed=true and date like '%1-%2-%'").arg(y).arg(m));
    }else if(ui->feeTypeComboBox->currentText().compare("应收费用") == 0){
        query.prepare(QString("select id, name, building_id, room_id, date, water, watt, gas, tv, property, mortage,payed from proprietor natural join month_bill where date like '%1-%2-%'").arg(y).arg(m));
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
    while(query.next()){
        int i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString()));
        //设置字符颜色
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
        model->setItem(i,3,new QStandardItem(query.value(3).toString() ));
        model->setItem(i,4,new QStandardItem(query.value(4).toString() ));
        model->setItem(i,5,new QStandardItem(query.value(5).toString()  ));
        model->setItem(i,6,new QStandardItem(query.value(6).toString()  ));
        model->setItem(i,7,new QStandardItem(query.value(7).toString()  ));
        model->setItem(i,8,new QStandardItem(query.value(8).toString()  ));
        model->setItem(i,9,new QStandardItem(query.value(9).toString()  ));
        model->setItem(i,10,new QStandardItem(query.value(10).toString()  ));
        if(query.value(11).toInt()==1){
            model->setItem(i,11,new QStandardItem("已交"));
        }else{
            model->setItem(i,11,new QStandardItem("未交"));
        }

    }
}
