#include "yearbillreportwidget.h"
#include "ui_yearbillreportwidget.h"

#include <QSqlQuery>
#include <QDate>
#include <QStandardItemModel>
#include <QDebug>

HTTP YearBillReportWidget::http;

YearBillReportWidget::YearBillReportWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::YearBillReportWidget)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("select min(date) min_date,max(date) max_date from month_bill");
    int begin_year = -1 , end_year = -1;
    while(query.next())
    {
        begin_year = query.value(0).toDate().toString("yyyy").toInt();
        end_year = query.value(1).toDate().toString("yyyy").toInt();
    }
    if(begin_year == -1 || end_year == -1)
    {
        qDebug() << "YEAR BILLREPORT WIDGET : ERROR FOR THE PARAMETER .";
    }

    while(begin_year<=end_year)
    {
        ui->yearomboBox->addItem(QString("%1").arg(begin_year));
         begin_year++;
    }

    ui->feeTypeComboBox->addItem("应收未收");
    ui->feeTypeComboBox->addItem("实收费用");
    ui->feeTypeComboBox->addItem("应收费用");

}

YearBillReportWidget::~YearBillReportWidget()
{
    delete ui;
}

void YearBillReportWidget::on_selectPushButton_clicked()
{
    QSqlQuery query;
    QString y = ui->yearomboBox->currentText();

    if(ui->feeTypeComboBox->currentText().compare("应收未收") == 0)
    {
        query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=false and date like '%1-%' group by id").arg(y));
    }
    else if(ui->feeTypeComboBox->currentText().compare("实收费用") == 0)
    {
        query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=true and date like '%1-%' group by id").arg(y));
    }
    else if(ui->feeTypeComboBox->currentText().compare("应收费用") == 0)
    {
        query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where  date like '%1-%' group by id").arg(y));
    }
    query.exec();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(11);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("水费"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("电费"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("天然气费"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("电视费用"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("物业费用"));
    model->setHeaderData(9,Qt::Horizontal,QString::fromUtf8("月房贷款"));
    model->setHeaderData(10,Qt::Horizontal,QString::fromUtf8("交费情况"));

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
        if(query.value(10).toInt()==1)
        {
            model->setItem(i,10,new QStandardItem("已交"));
        }
        else
        {
            model->setItem(i,10,new QStandardItem("未交"));
        }
    }
}

HTTP& YearBillReportWidget::getHTTP()
{
    return YearBillReportWidget::http;
}
