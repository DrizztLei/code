#include "delchargerwidget.h"
#include "ui_delchargerwidget.h"

// #include <QSqlTableModel>
#include <QDialog>
#include <QMessageBox>
#include <QNetworkReply>

// HTTP DelChargerWidget::http;

DelChargerWidget::DelChargerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelChargerWidget)
{
    ui->setupUi(this);

    if(list.size() != size)
    {
        for(int i = 0 ; i < size ; i++)
        {
            list.push_back(HTTP());
        }
    }

    /*

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
    */

    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setLength(0);
    list[0].postRequest("select login_id,role_type from user where role_type='CHARGER'");

    QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
    {
        model = new QStandardItemModel();
        model->setColumnCount(2);
        model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("登陆 ID"));
        model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("类别"));
        ui->tableView->setModel(model);

        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->tableView->setColumnWidth(0,100);

        int rowNum = 0;

        QList<QByteArray> info = list[0].getInfo().split('\n');

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
                if(j == 0)
                {
                    ui->comboBox->addItem(QString(info[sequence]));
                }
            }
        }
        ui->tableView->setModel(model);
    });
}

DelChargerWidget::~DelChargerWidget()
{
    delete ui;
}

void DelChargerWidget::on_pushButton_clicked()
{

    /*

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

    */

    list[1].clear();
    list[1].setFlag(true);
    list[1].setCommit(false);
    list[1].setRollback(false);
    list[1].setTransaction(false);
    list[1].setSync(true);
    list[1].setLength(1);

    list[1].addParameter(ui->comboBox->currentText());

    list[1].postRequest("delete from user where login_id = ?");

    {
        QList<QByteArray> info = list[1].getInfo().split('\n');
        bool exec = (QString(info[2]).compare("true") == 0);
        if(exec)
        {
            QMessageBox::information(0,"提示","删除成功",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(0,"提示","删除失败",QMessageBox::Ok);
        }
    }

    /*

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

    */

    list[2].setFlag(false);
    list[2].setCommit(false);
    list[2].setLength(0);
    list[2].postRequest("select login_id,role_type from user where role_type='CHARGER'");

    QObject::connect(list[2].getReply() , &QNetworkReply::finished , [&]()
    {
        int rowNum = 0;
        ui->comboBox->clear();
        model->clear();

        QList<QByteArray> info = list[2].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            rowNum = model->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                model->setItem(rowNum ,j ,new QStandardItem(QString(info[sequence])));
                if(j == 0)
                {
                    ui->comboBox->addItem(QString(info[sequence]));
                }
            }
        }
    });
}

/*

HTTP& DelChargerWidget::getHTTP()
{
    return DelChargerWidget::http;
}

*/
