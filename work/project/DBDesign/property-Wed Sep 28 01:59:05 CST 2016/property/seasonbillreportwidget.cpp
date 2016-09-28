#include "seasonbillreportwidget.h"
#include "ui_seasonbillreportwidget.h"

#include <QSqlQuery>
#include <QDate>
#include <QStandardItemModel>

// HTTP SeasonBillReportWidget::http;

SeasonBillReportWidget::SeasonBillReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeasonBillReportWidget)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("select min(date) min_date,max(date) max_date from month_bill");
    int begin_year;
    int end_year;
    while(query.next())
    {
        begin_year = query.value(0).toDate().toString("yyyy").toInt();
        end_year = query.value(1).toDate().toString("yyyy").toInt();
    }
    while(begin_year<=end_year)
    {
        ui->yearomboBox->addItem(QString("%1").arg(begin_year));
         begin_year++;
    }

    ui->seasonComboBox->addItem("第一季度");
    ui->seasonComboBox->addItem("第二季度");
    ui->seasonComboBox->addItem("第三季度");
    ui->seasonComboBox->addItem("第四季度");

    ui->feeTypeComboBox->addItem("应收未收");
    ui->feeTypeComboBox->addItem("实收费用");
    ui->feeTypeComboBox->addItem("应收费用");
}

SeasonBillReportWidget::~SeasonBillReportWidget()
{
    delete ui;
}

void SeasonBillReportWidget::on_selectPushButton_clicked()
{
    QSqlQuery query;
    QString y = ui->yearomboBox->currentText();
    QString m = ui->seasonComboBox->currentText();
    if(ui->feeTypeComboBox->currentText().compare("应收未收") == 0)
    {
        if(ui->seasonComboBox->currentText().compare("第一季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=false and (date like '%1-01-%' or date like '%2-02-%' or date like '%3-03-%') group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第二季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=false and (date like '%1-04-%' or date like '%2-05-%' or date like '%3-06-%') group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第三季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=false and (date like '%1-07-%' or date like '%2-08-%' or date like '%3-09-%') group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第四季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=false and (date like '%1-10-%' or date like '%2-11-%' or date like '%3-12-%') group by id").arg(y).arg(y).arg(y));
        }
    }
    else if(ui->feeTypeComboBox->currentText().compare("实收费用") == 0)
    {
        if(ui->seasonComboBox->currentText().compare("第一季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=true and (date like '%1-01-%' or date like '%2-02-%' or date like '%3-03-%') group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第二季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=true and (date like '%1-04-%' or date like '%2-05-%' or date like '%3-06-%') group by id ").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第三季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=true and (date like '%1-07-%' or date like '%2-08-%' or date like '%3-09-%') group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第四季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where payed=true and (date like '%1-10-%' or date like '%2-11-%' or date like '%3-12-%') group by id").arg(y).arg(y).arg(y));
        }
    }
    else if(ui->feeTypeComboBox->currentText().compare("应收费用") == 0)
    {
        if(ui->seasonComboBox->currentText().compare("第一季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id, sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where date like '%1-01-%' or date like '%2-02-%' or date like '%3-03-%' group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第二季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where date like '%1-04-%' or date like '%2-05-%' or date like '%3-06-%' group by id ").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第三季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where date like '%1-07-%' or date like '%2-08-%' or date like '%3-09-%' group by id").arg(y).arg(y).arg(y));
        }
        else if(ui->seasonComboBox->currentText().compare("第四季度") == 0)
        {
            query.prepare(QString("select id, name, building_id, room_id,  sum(water) s_water, sum(watt) s_watt, sum(gas) s_gas, sum(tv) s_tv, sum(property) s_property, sum(mortage) s_mortage,payed from proprietor natural join month_bill where date like '%1-10-%' or date like '%2-11-%' or date like '%3-12-%' group by id").arg(y).arg(y).arg(y));
        }
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

/*

HTTP& SeasonBillReportWidget::getHTTP()
{
    return SeasonBillReportWidget::http;
}

*/
