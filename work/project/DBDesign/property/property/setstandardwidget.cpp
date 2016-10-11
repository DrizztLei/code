#include "setstandardwidget.h"
#include "ui_setstandardwidget.h"

#include <QMessageBox>
#include <QNetworkReply>

// HTTP setStandardWidget::http;

setStandardWidget::setStandardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setStandardWidget)
{
    ui->setupUi(this);
    if(list.size() != size)
    {
        list.clear();
        for(int i = 0 ; i < size ; i++)
        {
            list.push_back(HTTP());
        }
    }

    /*

    model = new QSqlTableModel();
    model->setTable("standard");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"起效日期");
    model->setHeaderData(1,Qt::Horizontal,"水价（元/立方米）");
    model->setHeaderData(2,Qt::Horizontal,"电价（元/度）");
    model->setHeaderData(3,Qt::Horizontal,"天然气价（元/立方米）");
    model->setHeaderData(4,Qt::Horizontal,"有线电视（元/月）");
    model->setHeaderData(5,Qt::Horizontal,"月物业费（元/平方米）");
    model->setHeaderData(6,Qt::Horizontal,"房贷（元/月）");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    */

    model = new QStandardItemModel();

    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal,"起效日期");
    model->setHeaderData(1,Qt::Horizontal,"水价（元/立方米）");
    model->setHeaderData(2,Qt::Horizontal,"电价（元/度）");
    model->setHeaderData(3,Qt::Horizontal,"天然气价（元/立方米）");
    model->setHeaderData(4,Qt::Horizontal,"有线电视（元/月）");
    model->setHeaderData(5,Qt::Horizontal,"月物业费（元/平方米）");
    model->setHeaderData(6,Qt::Horizontal,"房贷（元/月）");

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();

    HTTP temp;

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(false);
    temp.setTransaction(false);
    temp.setRollback(false);
    temp.setSync(true);

    temp.setLength(0);

    temp.postRequest("select start_date , water_per_stere , watt_per_degree , gas_per_stere , tv_per_month , prop_per_sqare_month , mortage from standard");

    {
        int rowNum = 0;

        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;

        for(int i = 0 ; i < size ; i ++)
        {
            rowNum = model->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                model->setItem(rowNum , j , new QStandardItem(QString(info[sequence])));
            }
        }
    }
}

setStandardWidget::~setStandardWidget()
{
    delete ui;
}

void setStandardWidget::on_submitPushButton_clicked()
{

    HTTP temp;

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(true);
    temp.setRollback(false);
    temp.setTransaction(false);
    temp.setSync(true);
    temp.setLength(7);

    temp.addParameter(ui->startDateDateEdit->text());
    temp.addParameter(ui->waterStandarddoubleSpinBox->value());
    temp.addParameter(ui->wattStandarddoubleSpinBox->value());
    temp.addParameter(ui->gasStandarddoubleSpinBox->value());
    temp.addParameter(ui->tvStandarddoubleSpinBox->value());
    temp.addParameter(ui->propStandarddoubleSpinBox->value());
    temp.addParameter(ui->mortageStandarddoubleSpinBox->value());

    temp.postRequest("insert into standard values(?, ?, ?, ?, ?, ?, ?)");

    {
        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        if(temp.getFlag())
        {
            bool exec = (QString(info[2]).compare("true") == 0);
            if(exec)
            {
                QMessageBox::information(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("收费标准更新成功"),QMessageBox::Yes);
                ui->startDateDateEdit->setDate((new QDate())->currentDate());
                ui->waterStandarddoubleSpinBox->setValue(0);
                ui->wattStandarddoubleSpinBox->setValue(0);
                ui->gasStandarddoubleSpinBox->setValue(0);
                ui->tvStandarddoubleSpinBox->setValue(0);
                ui->propStandarddoubleSpinBox->setValue(0);
                ui->mortageStandarddoubleSpinBox->setValue(0);

                /*

                model->setTable("standard");
                model->select();
                model->setHeaderData(0,Qt::Horizontal,"起效日期");
                model->setHeaderData(1,Qt::Horizontal,"水价（元/立方米）");
                model->setHeaderData(2,Qt::Horizontal,"电价（元/度）");
                model->setHeaderData(3,Qt::Horizontal,"天然气价（元/立方米）");
                model->setHeaderData(4,Qt::Horizontal,"有线电视（元/月）");
                model->setHeaderData(5,Qt::Horizontal,"月物业费（元/平方米）");
                model->setHeaderData(6,Qt::Horizontal,"房贷（元/月）");

                */

                {
                    temp.clear();
                    temp.setCommit(false);
                    temp.setFlag(false);
                    temp.setTransaction(false);
                    temp.setRollback(false);
                    temp.setSync(true);

                    temp.setLength(0);

                    temp.postRequest("select start_date , water_per_stere , watt_per_degree , gas_per_stere , tv_per_month , prop_per_sqare_month , mortage from standard");

                    {

                        model->clear();

                        model->setColumnCount(7);
                        model->setHeaderData(0,Qt::Horizontal,"起效日期");
                        model->setHeaderData(1,Qt::Horizontal,"水价（元/立方米）");
                        model->setHeaderData(2,Qt::Horizontal,"电价（元/度）");
                        model->setHeaderData(3,Qt::Horizontal,"天然气价（元/立方米）");
                        model->setHeaderData(4,Qt::Horizontal,"有线电视（元/月）");
                        model->setHeaderData(5,Qt::Horizontal,"月物业费（元/平方米）");
                        model->setHeaderData(6,Qt::Horizontal,"房贷（元/月）");

                        int rowNum = 0;

                        QList<QByteArray> info = temp.getInfo().split('\n');

                        int size = info[0].toInt();
                        int rows = info[1].toInt();

                        int sequence;

                        for(int i = 0 ; i < size ; i ++)
                        {
                            rowNum = model->rowCount();
                            for(int j = 0 ; j < rows ; j++)
                            {
                                sequence = i*rows + j + 2;
                                model->setItem(rowNum , j , new QStandardItem(QString(info[sequence])));
                            }
                        }
                    }
                }

                ui->tableView->resizeColumnsToContents();
                ui->tableView->setSortingEnabled(true);
            }
            else
            {
                QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("收费标准更新失败"),QMessageBox::Yes);
            }
        }
        else
        {
            int sequence;
            for(int i = 0 ; i < size ; i ++)
            {
                for(int j = 0 ; j < rows ; j++)
                {
                    sequence = i*rows + j + 2;
                }
            }
        }
    }
}

/*

HTTP& setStandardWidget::getHTTP()
{
    return setStandardWidget::http;
}

*/
