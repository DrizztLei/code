#include "addchargerwidget.h"
#include "ui_addchargerwidget.h"

// #include <QSqlTableModel>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QNetworkReply>

// HTTP AddChargerWidget::http;

AddChargerWidget::AddChargerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddChargerWidget)
{
    ui->setupUi(this);

    // QSqlTableModel *model = new QSqlTableModel();

    if(list.size() != size)
    {
        list.clear();
        for(int i = 0 ; i < size ; i++)
        {
            list.push_back(HTTP());
        }
    }

    /*

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

    */

    list[0].clear();
    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setLength(0);
    list[0].setSync(true);

    list[0].postRequest("select login_id , role_type from user");

    QStandardItemModel * model = new QStandardItemModel();
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
        }
    }
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

    /*

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

    */

    list[0].setFlag(true);
    list[0].setCommit(false);
    list[0].setSync(true);
    list[0].setLength(2);
    list[0].addParameter(new_id);
    list[0].addParameter(md5);

    list[0].postRequest("insert into user values(?,?,'CHARGER')");

    QList<QByteArray> info = list[0].getInfo().split('\n');

    int size = info[0].toInt();
    int rows = info[1].toInt();

    int sequence;
    if(list[0].getFlag())
    {
        if(QString("true").compare(info[2]) == 0)
        {
            QMessageBox::information(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("添加成功"),QMessageBox::Yes);
            ui->loginIdLineEdit->clear();
            ui->passWdLineEdit->clear();

            /*

            QSqlTableModel *model = new QSqlTableModel();
            model->setTable("user");
            model->select();
            model->removeColumn(1);
            model->setHeaderData(0,Qt::Horizontal,QMessageBox::trUtf8("登陆Id"));
            model->setHeaderData(1,Qt::Horizontal,QMessageBox::trUtf8("类别"));
            ui->tableView->setModel(model);

            */
            {
                list[0].clear();
                list[0].setFlag(false);
                list[0].setCommit(false);
                list[0].setLength(0);
                list[0].setSync(true);

                list[0].postRequest("select login_id , role_type from user");

                QStandardItemModel * model = new QStandardItemModel();
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
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("添加失败"),QMessageBox::Yes);
        }
    }
    else
    {
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                qDebug() << info[sequence];
            }
        }
    }
}

/*

HTTP& AddChargerWidget::getHTTP()
{
    return AddChargerWidget::http;
}

*/
