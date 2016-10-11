#include "allroomproprietor.h"
#include "ui_allroomproprietor.h"

// #include <QSqlTableModel>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QDebug>
#include <QNetworkReply>

// HTTP AllRoomWidget::http;

AllRoomWidget::AllRoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllRoomProprietor)
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

    QSqlQuery query;
    //building comobox
    query.exec("select building_id from building");
    ui->comboBox->addItem("全部");
    
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->comboBox->addItem(id);
    }

    */
    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setLength(0);
    list[0].postRequest("select building_id from building");

    QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
    {
        ui->comboBox->addItem("全部");
        QList<QByteArray> info = list[0].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                ui->comboBox->addItem(QString(info[sequence]));
            }
        }
    });

    /*

    query.exec("select * from building");
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("层数"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("建成时间"));
    ui->buildingTableView->setModel(model);
    int row=0;
    while(query.next())
    {
        row = model->rowCount();
        model->setItem(row,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(row,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(row,2,new QStandardItem(query.value(2).toString() ));
    }

    ui->buildingTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->buildingTableView->setColumnWidth(0,150);

    */

    list[1].setFlag(false);
    list[1].setCommit(false);
    list[1].setLength(0);
    list[1].postRequest("select * from building");

    QObject::connect(list[1].getReply() , &QNetworkReply::finished , [&]()
    {
        QStandardItemModel* model = new QStandardItemModel();
        model->setColumnCount(3);
        model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
        model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("层数"));
        model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("建成时间"));
        ui->buildingTableView->setModel(model);
        int row = 0;

        QList<QByteArray> info = list[1].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            row = model->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                model->setItem(row,j,new QStandardItem(QString(info[sequence])));
            }
        }
    });

    //room

    /*

    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(4);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("入住情况"));
    query.clear();
    query.exec("select * from room");
    int rowNum=0;
    while(query.next()){
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        if(query.value(3).toInt()==1)
        {
            pmodel->setItem(rowNum,3,new QStandardItem("入住"));
            pmodel->item(rowNum,3)->setForeground(QBrush(QColor(255, 0, 0)));
        }
        else
        {
            pmodel->setItem(rowNum,3,new QStandardItem("未住"));
            pmodel->item(rowNum,3)->setForeground(QBrush(QColor(0, 0, 255)));
        }
    }

    ui->roomTableView->setModel(pmodel);
    //表头信息显示居左
    ui->roomTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->roomTableView->setColumnWidth(0,150);

    */

    list[2].setFlag(false);
    list[2].setCommit(false);
    list[2].setLength(0);
    list[2].postRequest("select * from room");

    QObject::connect(list[2].getReply() , &QNetworkReply::finished , [&]()
    {
        QStandardItemModel* pmodel = new QStandardItemModel();
        pmodel->setColumnCount(4);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("入住情况"));
        int rowNum = 0;

        QList<QByteArray> info = list[2].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            rowNum = pmodel->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 3 && info[sequence].toInt() == 1)
                {
                    pmodel->setItem(rowNum,3,new QStandardItem("入住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(255, 0, 0)));
                }
                else if ( j == 3)
                {
                    pmodel->setItem(rowNum,3,new QStandardItem("未住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(0, 0, 255)));
                }
                else
                {
                    pmodel->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
                }
            }
        }
        ui->roomTableView->setModel(pmodel);
        //表头信息显示居左
        ui->roomTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->roomTableView->setColumnWidth(0,150);
    });

}

AllRoomWidget::~AllRoomWidget()
{
    delete ui;
}

void AllRoomWidget::on_comboBox_currentIndexChanged(int index)
{

    /*

    qDebug() << index;
    //building comobox
    //room
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(4);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("入住情况"));
    QSqlQuery query;
    if(ui->comboBox->currentText().compare("全部")==0)
    {
         query.exec("select * from room");
    }
    else
    {
         query.exec(QString("select * from room where building_id=%1").arg(ui->comboBox->currentText()));
    }
    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        if(query.value(3).toInt()==1)
        {
                    pmodel->setItem(rowNum,3,new QStandardItem("入住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(255, 0, 0)));
        }
        else
        {
                    pmodel->setItem(rowNum,3,new QStandardItem("未住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(0, 0, 255)));
        }
    }
    ui->roomTableView->model()->deleteLater();
    ui->roomTableView->setModel(pmodel);
    //表头信息显示居左
    ui->roomTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->roomTableView->setColumnWidth(0,150);

    */

    list[3].setFlag(false);
    list[3].setCommit(false);
    list[3].setLength(0);

    if(ui->comboBox->currentText().compare("全部")==0)
    {
        list[3].postRequest("select * from room");
    }
    else
    {
        QString query = QString("select * from room where building_id=%1").arg(ui->comboBox->currentText());
        list[3].postRequest(query);
    }
    QObject::connect(list[3].getReply() , &QNetworkReply::finished , [&]()
    {
        QStandardItemModel* pmodel = new QStandardItemModel();
        pmodel->setColumnCount(4);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("面积"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("入住情况"));
        int rowNum = 0;

        QList<QByteArray> info = list[3].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            rowNum = pmodel->rowCount();
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 3 && info[sequence].toInt() == 1)
                {
                    pmodel->setItem(rowNum,3,new QStandardItem("入住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(255, 0, 0)));
                }
                else if ( j == 3)
                {
                    pmodel->setItem(rowNum,3,new QStandardItem("未住"));
                    pmodel->item(rowNum,3)->setForeground(QBrush(QColor(0, 0, 255)));
                }
                else
                {
                    pmodel->setItem(rowNum,j,new QStandardItem(QString(info[sequence])));
                }
            }
        }

        ui->roomTableView->setModel(pmodel);
        ui->roomTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->roomTableView->setColumnWidth(0,150);
    });
}

/*

HTTP& AllRoomWidget::getHTTP()
{
    return AllRoomWidget::http;
}

*/
