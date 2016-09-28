#include "addchargerwidget.h"
#include "ui_addchargerwidget.h"

#include <QSqlTableModel>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QNetworkReply>

HTTP AddChargerWidget::http;

AddChargerWidget::AddChargerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddChargerWidget)
{
    ui->setupUi(this);
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("user");
    model->select();
    model->removeColumn(1);
    model->setHeaderData(0,Qt::Horizontal,"登陆Id");
    model->setHeaderData(1,Qt::Horizontal,"类别");
    ui->tableView->setModel(model);
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);

    // need complete here .

}

AddChargerWidget::~AddChargerWidget()
{
    delete ui;
}

void AddChargerWidget::on_addNewpushButton_clicked()
{
    QString new_id = ui->loginIdLineEdit->text();
    QString pwd = ui->passWdLineEdit->text();
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());
    QSqlQuery q;
    q.prepare("insert into user values(?,?,'CHARGER')");
    q.addBindValue(new_id);
    q.addBindValue(md5);
    if(q.exec())
    {
        QMessageBox::information(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("添加成功"),QMessageBox::Yes);
        ui->loginIdLineEdit->clear();
        ui->passWdLineEdit->clear();
        QSqlTableModel *model = new QSqlTableModel();
        model->setTable("user");
        model->select();
        model->removeColumn(1);
        model->setHeaderData(0,Qt::Horizontal,QMessageBox::trUtf8("登陆Id"));
        model->setHeaderData(1,Qt::Horizontal,QMessageBox::trUtf8("类别"));
        ui->tableView->setModel(model);
    }
    else
    {
         QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("添加失败"),QMessageBox::Yes);
    }
}

HTTP& AddChargerWidget::getHTTP()
{
    return AddChargerWidget::http;
}
