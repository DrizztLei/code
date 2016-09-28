#include "delchargerwidget.h"
#include "ui_delchargerwidget.h"

#include <QSqlTableModel>
#include <QDialog>
#include <QMessageBox>

HTTP DelChargerWidget::http;

DelChargerWidget::DelChargerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelChargerWidget)
{
    ui->setupUi(this);
    //model for table
    model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("登陆 ID"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("类别"));
    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);

    QSqlQuery q;
    q.exec("select login_id,role_type from user where role_type='CHARGER'");

    int i=0;
    while(q.next())
    {
        i=model->rowCount();
        model->setItem(i,0,new QStandardItem(q.value(0).toString()));
        model->setItem(i,1,new QStandardItem(q.value(1).toString()));
        ui->comboBox->addItem(q.value(0).toString());
    }
    ui->tableView->setModel(model);

}

DelChargerWidget::~DelChargerWidget()
{
    delete ui;
}

void DelChargerWidget::on_pushButton_clicked()
{

    QSqlQuery q;
    q.prepare("delete from user where login_id = ?");
    q.addBindValue(ui->comboBox->currentText());
    if(q.exec())
    {
        QMessageBox::information(0,"提示","删除成功",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(0,"提示","删除失败",QMessageBox::Ok);
        return;
    }
    q.exec("select login_id,role_type from user where role_type='CHARGER'");
    int i=0;
    ui->comboBox->clear();
    model->clear();
    while(q.next())
    {
        i=model->rowCount();
        model->setItem(i,0,new QStandardItem(q.value(0).toString()));
        model->setItem(i,1,new QStandardItem(q.value(1).toString()));
        ui->comboBox->addItem(q.value(0).toString());
    }
}

HTTP& DelChargerWidget::getHTTP()
{
    return DelChargerWidget::http;
}
