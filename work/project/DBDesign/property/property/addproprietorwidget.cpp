#include "addproprietorwidget.h"
#include "ui_addproprietorwidget.h"
#include "http.h"

#include <QRegExp>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkReply>
#include <unistd.h>


AddProprietorWidget::AddProprietorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProprietorWidget)
{
    ui->setupUi(this);

    if(list.size() == 0)
    {
        for(int i = 0 ; i < this->size; i++)
        {
            list.push_back(HTTP());
        }
    }

    // QSqlQuery query;

    // building

    /*

    query.exec("select building_id from building");

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->buildingComboBox->addItem(id);
    }

    */

    /*------------------------------------------*/

    list[0].setCommit(false);
    list[0].setFlag(false);
    list[0].setLength(0);
    list[0].setSync(true);

    list[0].postRequest("select building_id from building");

    {
        // QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
        //{
            // qDebug() << list[0].getInfo();
            QList<QByteArray> info = list[0].getInfo().split('\n');

            int size = info[0].toInt();
            int rows = info[1].toInt();

            int sequence;
            for(int i = 0 ; i < size ; i ++)
            {
                for(int j = 0 ; j < rows ; j++)
                {
                    // qDebug() << info[i*rows + j + 2];
                    sequence = i*rows + j + 2;
                    ui->buildingComboBox->addItem(QString(info[sequence]));
                }
            }
        //});
    }


    /*------------------------------------------*/

    //proprietor

    // query.exec("select id,name,building_id, room_id,own_date from proprietor");
    /*

    QStandardItemModel* pmodel = new QStandardItemModel();
     = pmodel;
    pmodel->setColumnCount(5);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));
    ui->proprietorTableView->setModel(pmodel);

    //表头信息显示居左

    ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->proprietorTableView->setColumnWidth(0,150);

    */
    /*

    int rowNum=0;

    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
    }

    */

    list[1].setCommit(false);
    list[1].setFlag(false);
    list[1].setLength(0);
    list[1].setSync(true);

    list[1].postRequest("select id,name,building_id, room_id,own_date from proprietor");

    //QObject::connect(list[1].getReply() , &QNetworkReply::finished , [&]()
    //{
    {
        QStandardItemModel* pmodel = new QStandardItemModel();
        old = pmodel;
        pmodel->setColumnCount(5);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));
        ui->proprietorTableView->setModel(pmodel);

        //表头信息显示居左

        ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->proprietorTableView->setColumnWidth(0,150);

        int rowNum=0;

        // need complete

        QList<QByteArray> info = list[1].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;

        for(int i = 0 ; i < size ; i ++)
        {
            rowNum = pmodel->rowCount();

            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                pmodel->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
            }
        }
    }
    //});

    list[2].setCommit(false);
    list[2].setFlag(false);
    list[2].setLength(1);
    list[2].setSync(true);

    list[2].addParameter(ui->buildingComboBox->currentText());

    list[2].postRequest("select room_id from room where building_id=? and stayed = false");

    //QObject::connect(list[2].getReply() , &QNetworkReply::finished , [&]()
    //{
    {
        ui->roomComboBox->clear();

        QList<QByteArray> info = list[2].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();
        int sequence;

        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                // qDebug() << info[i*rows + j + 2];
                sequence = i*rows + j + 2;
                ui->roomComboBox->addItem(QString(info[sequence]));
            }
        }
    }
    //});

    /*

    //room

    ui->roomComboBox->clear();

    query.prepare("select room_id from room where building_id=? and stayed = false");
    QVariant value = ui->buildingComboBox->currentText();

    // query.addBindValue(ui->buildingComboBox->currentText());

    query.addBindValue(value);
    query.exec();

    while(query.next())
    {
        QString id = query.value(0).toString();
        qDebug() << "id : " << id;
        ui->roomComboBox->addItem(id);
    }

    */

    list[3].setCommit(false);
    list[3].setFlag(false);
    list[3].setLength(0);
    list[3].setSync(true);
    // list[3].postRequest("select building_id, room_id, area from room where stayed = false and building_id like ?");
    list[3].postRequest("select building_id, room_id, area from room where stayed = false");

    //QObject::connect(list[3].getReply() , &QNetworkReply::finished , [&]()
    //{
        /*

        qDebug() << "PARAMETER : " << list[3].getParameter();
        QByteArray temp;
        QString a = "1#\t";
        temp.append("1#\t" + a);
        qDebug() << "TEMP : " << temp;

        */
    {
        QStandardItemModel* model = new QStandardItemModel();
        model->setColumnCount(3);
        model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
        model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
        model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
        ui->tableView->setModel(model);

        // 表头信息显示居左

        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->tableView->setColumnWidth(0,100);
        int k=0;

        QList<QByteArray> info = list[3].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();
        int sequence;

        for(int i = 0 ; i < size ; i ++)
        {
            k = model->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                // qDebug() << info[i*rows + j + 2];
                sequence = i*rows + j + 2;
                model->setItem(k , j , new QStandardItem(QString(info[sequence])));
            }
        }
    }
    //});

    /*
    query.exec("select building_id, room_id, area from room where stayed = false");

    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    ui->tableView->setModel(model);

    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    int i=0;

    while(query.next())
    {
        i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString()));
        model->setItem(i,1,new QStandardItem(query.value(1).toString()));
        model->setItem(i,2,new QStandardItem(query.value(2).toString()));
    }

    */
}

AddProprietorWidget::~AddProprietorWidget()
{
    delete ui;
}

void AddProprietorWidget::on_buildingComboBox_currentIndexChanged(int index)
{
    // http from 4

    ui->roomComboBox->clear();

    // QSqlQuery query;

    /*

    query.prepare("select room_id from room where building_id=? and stayed = false");
    query.addBindValue(ui->buildingComboBox->currentText());
    QString parameter = (index+1) + "#";
    // parameter doesn't add in it .
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    list[4].clear();
    list[4].setFlag(false);
    list[4].setCommit(false);
    list[4].setSync(true);
    list[4].setLength(1);
    list[4].addParameter(ui->buildingComboBox->currentText());

    list[4].postRequest("select room_id from room where building_id=? and stayed = false");

    QList<QByteArray> info = list[4].getInfo().split('\n');

    int size = info[0].toInt();
    int rows = info[1].toInt();

    int sequence;
    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            QString id = info[sequence];
            ui->roomComboBox->addItem(id);
        }
    }

    /*

    //update proprietor table view
    query.prepare("select id,name, building_id, room_id, own_date from proprietor where building_id=? ");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    ui->proprietorTableView->model()->deleteLater();
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(5);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));

    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
    }
    ui->proprietorTableView->setModel(pmodel);
    //表头信息显示居左
    ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->proprietorTableView->setColumnWidth(0,150);

    */

    list[5].clear();
    list[5].setFlag(false);
    list[5].setCommit(false);
    list[5].setSync(true);
    list[5].setLength(1);
    list[5].addParameter(ui->buildingComboBox->currentText());

    list[5].postRequest("select id,name, building_id, room_id, own_date from proprietor where building_id=? ");

    ui->proprietorTableView->model()->deleteLater();
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(5);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));
    int rowNum;

    info = list[5].getInfo().split('\n');

    size = info[0].toInt();
    rows = info[1].toInt();

    sequence = 0 , rowNum = 0;
    for(int i = 0 ; i < size ; i ++)
    {
        rowNum = pmodel->rowCount();
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            pmodel->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
        }
    }

    ui->proprietorTableView->setModel(pmodel);
    //表头信息显示居左
    ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->proprietorTableView->setColumnWidth(0,150);


    /*

    //update room table view
    query.prepare("select building_id, room_id, area from room where stayed = false and building_id=?");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();

    ui->tableView->model()->deleteLater();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    int i=0;
    while(query.next())
    {
        i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
    }

    */

    list[6].clear();
    list[6].setFlag(false);
    list[6].setCommit(false);
    list[6].setSync(true);
    list[6].setLength(1);
    list[6].addParameter(ui->buildingComboBox->currentText());

    list[6].postRequest("select building_id, room_id, area from room where stayed = false and building_id=?");

    ui->tableView->model()->deleteLater();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));

    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);

    info = list[6].getInfo().split('\n');

    size = info[0].toInt();
    rows = info[1].toInt();

    sequence = 0 , rowNum = 0;

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

void AddProprietorWidget::on_pushButton_clicked()
{
    if(ui->proprietorLineEdit->text().length()!=18 && ui->proprietorLineEdit->text().length()!=15)
    {
        ui->proprietorLineEdit->clear();
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("身份证号错误"),QMessageBox::Yes);
        return;
    }
    if(ui->nameLineEdit->text().length()==0)
    {
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("姓名不能为空"),QMessageBox::Yes);
        return;
    }
    if(ui->organizationLineEdit->text().length()==0)
    {
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("工作单位不能为空"),QMessageBox::Yes);
        return;
    }
    if(ui->phone1LineEdit->text().length()==0)
    {
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("电话号码不能为空"),QMessageBox::Yes);
        return;
    }

    // http from 7

    int index = 7 , postSize = 0 , sequence = 0 , size = 0 , rows = 0;

    QList<QByteArray> info;

    QString postSQL = "";

    /*

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(false);
    list[index].setSync(true);
    list[index].setLength(postSize);
    // list[index].addParameter();
    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
        }
    }

    index++;

    */


    QString ID = ui->proprietorLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString organization = ui->organizationLineEdit->text();
    QString building_id = ui->buildingComboBox->currentText();
    QString room_id = ui->roomComboBox->currentText();
    QString own_date = ui->ownDateDateTimeEdit->text();

    // QSqlQuery query;select id,name,building_id, room_id,own_date from proprietor

    bool res ;

    /*

    QSqlDatabase::database().transaction();
    bool res = false;

    query.prepare("insert into proprietor values(?,?,?,?,?,?)");
    query.addBindValue(ID);
    query.addBindValue(name);
    query.addBindValue(organization);
    query.addBindValue(building_id);
    query.addBindValue(room_id);
    query.addBindValue(own_date);
    res = query.exec();

    */

    postSize = 6;
    postSQL = "insert into proprietor values(?,?,?,?,?,?)";

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(true);
    list[index].setSync(true);
    list[index].setLength(postSize);

    list[index].addParameter(ID);
    list[index].addParameter(name);
    list[index].addParameter(organization);
    list[index].addParameter(building_id);
    list[index].addParameter(room_id);
    list[index].addParameter(own_date);

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');

    size = info[0].toInt();
    rows = info[1].toInt();

    if(list[index].getFlag())
    {
        res = (QString(info[2]).compare("true") == 0);
    }

    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
        }
    }

    index++;

    /*

    //phone_num
    query.prepare("insert into proprietor_phone_num values(?,?)");
    query.addBindValue(ui->phone1LineEdit->text());
    query.addBindValue(ui->proprietorLineEdit->text());
    res &= query.exec();

    */

    postSize = 2;
    postSQL = "insert into proprietor_phone_num values(?,?)";

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(true);
    list[index].setSync(true);
    list[index].setLength(postSize);
    list[index].addParameter(ui->phone1LineEdit->text());
    list[index].addParameter(ui->proprietorLineEdit->text());
    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    if(list[index].getFlag())
    {
        res &= (QString(info[2]).compare("true") == 0);
    }

    index++;

    /*

    if(ui->phone2Line->text().length()>1)
    {
        query.prepare("insert into proprietor_phone_num values(?,?)");
        query.addBindValue(ui->phone2Line->text());
        query.addBindValue(ui->proprietorLineEdit->text());
        res &=  query.exec();
    }

    */

    if(ui->phone2Line->text().length() > 1)
    {
        postSize = 2;
        postSQL = "insert into proprietor_phone_num values(?,?)";

        list[index].clear();
        list[index].setCommit(false);
        list[index].setFlag(true);
        list[index].setSync(true);
        list[index].setLength(postSize);

        list[index].addParameter(ui->phone2Line->text());
        list[index].addParameter(ui->proprietorLineEdit->text());

        list[index].postRequest(postSQL);

        info = list[index].getInfo().split('\n');
        size = info[0].toInt();
        rows = info[1].toInt();

        if(list[index].getFlag())
        {
            res &= (QString(info[2]).compare("true") == 0);
        }

        index++;
    }

    /*

    query.prepare("update room set stayed = true where building_id=? and room_id=?");
    query.addBindValue(building_id);
    query.addBindValue(room_id);
    res &= query.exec();

    */

    postSize = 2;
    postSQL = "update room set stayed = true where building_id=? and room_id=?";

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(true);
    list[index].setSync(true);
    list[index].setLength(postSize);

    list[index].addParameter(building_id);
    list[index].addParameter(room_id);

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    if(list[index].getFlag())
    {
        res &= (QString(info[2]).compare("true") == 0);
    }

    index++;



    /*

    if(!res)
    {
        QSqlDatabase::database().rollback();
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作失败"),QMessageBox::Yes);
        return;
    }
    else
    {
        QSqlDatabase::database().commit();
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作成功"),QMessageBox::Yes);
        return;
    }

    */

    if(!res)
    {
        HTTP temp;
        temp.setLength(0);
        temp.setRollback(true);
        temp.setSync(true);
        temp.postRequest("");
        // QSqlDatabase::database().rollback();
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作失败"),QMessageBox::Yes);
        return;
    }
    else
    {
        HTTP temp;
        temp.setLength(0);
        temp.setCommit(true);
        temp.setSync(true);
        temp.postRequest("");
        // QSqlDatabase::database().commit();
        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作成功"),QMessageBox::Yes);
    }

    /*

    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = false");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    postSize = 1;
    postSQL = "select room_id from room where building_id=? and stayed = false";

    ui->roomComboBox->clear();

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(false);
    list[index].setSync(true);
    list[index].setLength(postSize);

    list[index].addParameter(ui->buildingComboBox->currentText());

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            if(j == 0)
            {
                QString id = QString(info[sequence]);
                ui->roomComboBox->addItem(id);
            }
        }
    }

    index++;

    /*

    //update proprietor table view
    query.prepare("select id,name, building_id, room_id, own_date from proprietor where building_id=? ");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    ui->proprietorTableView->model()->deleteLater();
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(5);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));

    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
    }
    ui->proprietorTableView->setModel(pmodel);
    //表头信息显示居左
    ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->proprietorTableView->setColumnWidth(0,150);

    */
    postSize = 1;
    postSQL = "select id,name, building_id, room_id, own_date from proprietor where building_id=? ";

    ui->proprietorTableView->model()->deleteLater();

    old->deleteLater();

    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(5);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("入住日期"));
    int rowNum = 0;

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(false);
    list[index].setSync(true);
    list[index].setLength(postSize);

    list[index].addParameter(ui->buildingComboBox->currentText());

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    for(int i = 0 ; i < size ; i ++)
    {
        rowNum = pmodel->rowCount();
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            pmodel->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
        }
    }

    ui->proprietorTableView->setModel(pmodel);
    //表头信息显示居左
    ui->proprietorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->proprietorTableView->setColumnWidth(0,150);

    index++;

    /*
    //update room table view
    query.prepare("select building_id, room_id, area from room where stayed = false and building_id=?");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();

    ui->tableView->model()->deleteLater();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    int i=0;
    while(query.next())
    {
        i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
    }

    */

    postSize = 1;
    postSQL = "select building_id, room_id, area from room where stayed = false and building_id=?";

    ui->tableView->model()->deleteLater();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(false);
    list[index].setTransaction(false);
    list[index].setSync(true);
    list[index].setLength(postSize);

    list[index].addParameter(ui->buildingComboBox->currentText());

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');
    size = info[0].toInt();
    rows = info[1].toInt();

    for(int i = 0 ; i < size ; i ++)
    {
        rowNum = model->rowCount();
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            model->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
        }
    }
    index++;
}

/*

HTTP& AddProprietorWidget::getHTTP()
{
    return AddProprietorWidget::http;
}

*/
