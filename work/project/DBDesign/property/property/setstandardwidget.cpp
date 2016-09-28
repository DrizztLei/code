#include "setstandardwidget.h"
#include "ui_setstandardwidget.h"

#include <QMessageBox>

HTTP setStandardWidget::http;

setStandardWidget::setStandardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setStandardWidget)
{
    ui->setupUi(this);
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
}

setStandardWidget::~setStandardWidget()
{
    delete ui;
}

void setStandardWidget::on_submitPushButton_clicked()
{
    QSqlQuery q;
    q.prepare("insert into standard values(?, ?, ?, ?, ?, ?, ?)");
    q.addBindValue(ui->startDateDateEdit->text());
    q.addBindValue(ui->waterStandarddoubleSpinBox->value());
    q.addBindValue(ui->wattStandarddoubleSpinBox->value());
    q.addBindValue(ui->gasStandarddoubleSpinBox->value());
    q.addBindValue(ui->tvStandarddoubleSpinBox->value());
    q.addBindValue(ui->propStandarddoubleSpinBox->value());
    q.addBindValue(ui->mortageStandarddoubleSpinBox->value());
    if(q.exec())
    {
        QMessageBox::information(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("收费标准更新成功"),QMessageBox::Yes);
        ui->startDateDateEdit->setDate((new QDate())->currentDate());
        ui->waterStandarddoubleSpinBox->setValue(0);
        ui->wattStandarddoubleSpinBox->setValue(0);
        ui->gasStandarddoubleSpinBox->setValue(0);
        ui->tvStandarddoubleSpinBox->setValue(0);
        ui->propStandarddoubleSpinBox->setValue(0);
        ui->mortageStandarddoubleSpinBox->setValue(0);
        model->clear();
        model->setTable("standard");
        model->select();
        model->setHeaderData(0,Qt::Horizontal,"起效日期");
        model->setHeaderData(1,Qt::Horizontal,"水价（元/立方米）");
        model->setHeaderData(2,Qt::Horizontal,"电价（元/度）");
        model->setHeaderData(3,Qt::Horizontal,"天然气价（元/立方米）");
        model->setHeaderData(4,Qt::Horizontal,"有线电视（元/月）");
        model->setHeaderData(5,Qt::Horizontal,"月物业费（元/平方米）");
        model->setHeaderData(6,Qt::Horizontal,"房贷（元/月）");
        ui->tableView->resizeColumnsToContents();
        ui->tableView->setSortingEnabled(true);
    }
    else
    {
         QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("收费标准更新失败"),QMessageBox::Yes);
    }
}

HTTP& setStandardWidget::getHTTP()
{
    return setStandardWidget::http;
}
