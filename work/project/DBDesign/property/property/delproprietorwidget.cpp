#include "delproprietorwidget.h"
#include "ui_delproprietorwidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QNetworkReply>

// HTTP DelProprietorWidget::http;

DelProprietorWidget::DelProprietorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelProprietorWidget)
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

    QSqlQuery query;
    //building
    query.exec("select building_id from building");

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->buildComboBox->addItem(id);
    }

    */

    list[0].clear();
    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setSync(true);

    list[0].setLength(0);

    list[0].postRequest("select building_id from building");

    QList<QByteArray> info = list[0].getInfo().split('\n');

    int size = info[0].toInt();
    int rows = info[1].toInt();

    int sequence;

    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            ui->buildComboBox->addItem(QString(info[sequence]));
        }
    }

    list[1].clear();
    list[1].setCommit(false);
    list[1].setFlag(false);
    list[1].setSync(true);

    list[1].setLength(0);

    list[1].postRequest("select id,name,organization,building_id, room_id,own_date from proprietor");

//    QObject::connect(list[1].getReply() , &QNetworkReply::finished , [&]()
    {
        QStandardItemModel* pmodel = new QStandardItemModel();

        pmodel->setColumnCount(6);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
        ui->tableView->setModel(pmodel);
        //表头信息显示居左
        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->tableView->setColumnWidth(0,150);

        int rowNum = pmodel->rowCount();

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
                QString trip = QString(info[sequence]);
                pmodel->setItem(rowNum , j , new QStandardItem(trip));
            }
        }
    }

    {

        list[2].clear();
        list[2].setSync(true);
        list[2].setCommit(false);
        list[2].setFlag(false);

        list[2].setLength(1);

        list[2].addParameter(ui->buildComboBox->currentText());

        list[2].postRequest("select room_id from room where building_id=? and stayed = true");

        QList<QByteArray> info = list[2].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;

        ui->roomComboBox->clear();

        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                ui->roomComboBox->addItem(QString(info[sequence]));
            }
        }
    }

    {
        list[3].clear();
        list[3].setCommit(false);
        list[3].setFlag(false);
        list[3].setSync(true);

        list[3].setLength(2);

        list[3].addParameter(ui->buildComboBox->currentText());
        list[3].addParameter(ui->roomComboBox->currentText());

        list[3].postRequest("select id,name from proprietor where building_id=? and room_id=?");

//        QObject::connect(list[3].getReply() , &QNetworkReply::finished , [&]()
//        {
            {
                QList<QByteArray> info = list[3].getInfo().split('\n');

                int size = info[0].toInt();
                int rows = info[1].toInt();

                int sequence;
                for(int i = 0 ; i < size ; i ++)
                {
                    for(int j = 0 ; j < rows ; j++)
                    {
                        sequence = i*rows + j + 2;
                        if(j == 0)
                        {
                            ui->proprietorIdLabel->setText(QString(info[sequence]));
                        }
                        else if(j == 1)
                        {
                            ui->proprietorLabel->setText(QString(info[sequence]));
                        }
                    }
                }
            }
//        });
    }


    /*

    //proprietor
    query.exec("select id,name,organization,building_id, room_id,own_date from proprietor");
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(6);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
    ui->tableView->setModel(pmodel);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,150);
    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    */

//);

    /*

    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    /*

    list[2].setCommit(false);
    list[2].setFlag(false);
    list[2].setLength(1);
    list[2].addParameter(ui->buildComboBox->currentText());

    list[2].postRequest("select room_id from room where building_id=? and stayed = true");

    QObject::connect(list[2].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[2].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                ui->roomComboBox->addItem(QString(info[sequence]));
            }
        }
    });

    */

    /*

    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }

    */

    /*

    ui->buildComboBox->setCurrentText("1#");
    ui->roomComboBox->setCurrentText("101");

    list[3].setCommit(false);
    list[3].setFlag(false);
    list[3].setLength(2);
    list[3].addParameter(ui->buildComboBox->currentText());
    list[3].addParameter(ui->roomComboBox->currentText());
    list[3].postRequest("select id,name from proprietor where building_id=? and room_id=?");

    QObject::connect(list[3].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[3].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 0)
                {
                    ui->proprietorIdLabel->setText(QString(info[sequence]));
                }
                else if(j == 1)
                {
                    ui->proprietorLabel->setText(QString(info[sequence]));
                }
            }
        }
    });

    */

}

DelProprietorWidget::~DelProprietorWidget()
{
    delete ui;
}

void DelProprietorWidget::on_buildComboBox_currentIndexChanged(int index)
{
    //room

    /*

    QSqlQuery query;
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    ui->roomComboBox->clear();

    list[4].clear();
    list[4].setCommit(false);
    list[4].setFlag(false);
    list[4].setLength(1);
    list[4].addParameter(ui->buildComboBox->currentText());
    list[4].postRequest("select room_id from room where building_id=? and stayed = true");

    QObject::connect(list[4].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[4].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i * rows + j + 2;
                ui->roomComboBox->addItem(QString(info[sequence]));
            }
        }

        // select the room .
        {

            list[6].clear();
            list[6].setCommit(false);
            list[6].setFlag(false);
            list[6].setLength(2);
            list[6].addParameter(ui->buildComboBox->currentText());
            list[6].addParameter(ui->roomComboBox->currentText());
            list[6].postRequest("select id,name from proprietor where building_id=? and room_id = ?");

            QObject::connect(list[6].getReply() , &QNetworkReply::finished , [&]()
            {
                QList<QByteArray> info = list[6].getInfo().split('\n');

                int size = info[0].toInt();
                int rows = info[1].toInt();

                int sequence;
                for(int i = 0 ; i < size ; i ++)
                {
                    for(int j = 0 ; j < rows ; j++)
                    {
                        sequence = i*rows + j + 2;
                        if(j == 0)
                        {
                            ui->proprietorIdLabel->setText(QString(info[sequence]));
                        }
                        else if(j == 1)
                        {
                            ui->proprietorLabel->setText(QString(info[sequence]));
                        }
                    }
                }
            });
        }
    });

    /*

    //proprietor
    query.prepare("select id,name,organization,building_id, room_id,own_date from proprietor where building_id=?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    ui->tableView->model()->deleteLater();
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(6);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
    ui->tableView->setModel(pmodel);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,150);
    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    */

    list[5].clear();
    list[5].setCommit(false);
    list[5].setFlag(false);
    list[5].setLength(1);
    list[5].addParameter(ui->buildComboBox->currentText());
    list[5].postRequest("select id,name,organization,building_id, room_id,own_date from proprietor where building_id=?");

    QObject::connect(list[5].getReply() , &QNetworkReply::finished , [&]()
    {

        ui->tableView->model()->deleteLater();
        QStandardItemModel* pmodel = new QStandardItemModel();
        pmodel->setColumnCount(6);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
        ui->tableView->setModel(pmodel);
        //表头信息显示居左
        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->tableView->setColumnWidth(0,150);
        int rowNum = 0;

        QList<QByteArray> info = list[5].getInfo().split('\n');

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
    });

    /*

    //label
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }

    */

    /*

    list[6].clear();
    list[6].setCommit(false);
    list[6].setFlag(false);
    list[6].setLength(2);
    list[6].addParameter(ui->buildComboBox->currentText());
    list[6].addParameter(ui->roomComboBox->currentText());
    list[6].postRequest("select id,name from proprietor where building_id=? and room_id = ?");

    QObject::connect(list[6].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[6].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 0)
                {
                    ui->proprietorIdLabel->setText(QString(info[sequence]));
                }
                else if(j == 1)
                {
                    ui->proprietorLabel->setText(QString(info[sequence]));
                }
            }
        }
    });

    */
}

void DelProprietorWidget::on_roomComboBox_currentIndexChanged(int index)
{
    /*

    qDebug () << index;
    QSqlQuery query;

    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }

    */

    if(index == -1)
    {
        return;
    }

    list[7].clear();
    list[7].setCommit(false);
    list[7].setFlag(false);
    list[7].setLength(2);
    list[7].addParameter(ui->buildComboBox->currentText());
    list[7].addParameter(ui->roomComboBox->currentText());
    list[7].postRequest("select id,name from proprietor where building_id=? and room_id = ?");

    QObject::connect(list[7].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[7].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 0)
                {
                    ui->proprietorIdLabel->setText(QString(info[sequence]));
                }
                else if(j == 1)
                {
                    ui->proprietorLabel->setText(QString(info[sequence]));
                }
            }
        }
    });

}

void DelProprietorWidget::on_pushButton_clicked()
{
    // start from 8

    /*

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    bool res = false;
    //delete phone num
    query.prepare("delete from proprietor_phone_num where id=?");
    query.addBindValue(ui->proprietorIdLabel->text());
    res &= query.exec();
    //delete prop
    query.prepare("delete from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    res = query.exec();
    //update room
    query.prepare("update room set stayed=false where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    res &= query.exec();
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
    QString build , room , id ;

    build = ui->buildComboBox->currentText();
    room = ui->roomComboBox->currentText();
    id = ui->proprietorIdLabel->text();

    HTTP temp;
    bool res = true;

    temp.clear();
    temp.setSync(true);
    temp.setTransaction(true);

    temp.setLength(0);

    temp.postRequest("");

    temp.clear();
    temp.setTransaction(false);
    temp.setFlag(true);
    temp.setSync(true);
    temp.setRollback(false);
    temp.setCommit(false);
    temp.setLength(1);

    temp.addParameter(id);

    temp.postRequest("delete from proprietor_phone_num where id=?");
    {
        QList<QByteArray> info = temp.getInfo().split('\n');
        res &= (QString(info[2]).compare("true") == 0);
    }

    temp.clear();
    temp.setTransaction(false);
    temp.setFlag(true);
    temp.setSync(true);
    temp.setRollback(false);
    temp.setCommit(false);
    temp.setLength(1);

    temp.addParameter(id);

    temp.postRequest("delete from month_bill where id=?");
    {
        QList<QByteArray> info = temp.getInfo().split('\n');
        res &= (QString(info[2]).compare("true") == 0);
    }

    temp.clear();
    temp.setTransaction(false);
    temp.setFlag(true);
    temp.setSync(true);
    temp.setRollback(false);
    temp.setCommit(false);
    temp.setLength(2);

    temp.addParameter(build);
    temp.addParameter(room);

    temp.postRequest("delete from proprietor where building_id=? and room_id = ?");
    {
        QList<QByteArray> info = temp.getInfo().split('\n');
        res &= (QString(info[2]).compare("true") == 0);
    }

    temp.clear();
    temp.setTransaction(false);
    temp.setFlag(true);
    temp.setSync(true);
    temp.setRollback(false);
    temp.setCommit(false);
    temp.setLength(2);

    temp.addParameter(build);
    temp.addParameter(room);

    temp.postRequest("update room set stayed=false where building_id=? and room_id = ?");
    {
        QList<QByteArray> info = temp.getInfo().split('\n');
        res &= (QString(info[2]).compare("true") == 0);
    }

    if(!res)
    {
        temp.clear();
        temp.setTransaction(false);
        temp.setFlag(false);
        temp.setSync(true);
        temp.setRollback(true);
        temp.setCommit(false);
        temp.setLength(0);
        temp.postRequest("");

        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作失败"),QMessageBox::Yes);
        return;
    }
    else
    {
        temp.clear();
        temp.setTransaction(false);
        temp.setFlag(false);
        temp.setSync(true);
        temp.setRollback(false);
        temp.setCommit(true);
        temp.setLength(0);
        temp.postRequest("");

        QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作成功"),QMessageBox::Yes);
    }

    // from num 11
    //update table view

    /*

    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    ui->roomComboBox->clear();

    list[11].clear();
    list[11].setCommit(false);
    list[11].setFlag(false);
    list[11].setLength(1);
    list[11].addParameter(ui->buildComboBox->currentText());
    list[11].postRequest("select room_id from room where building_id=? and stayed = true");

    QObject::connect(list[11].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[11].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                ui->roomComboBox->addItem(QString(info[sequence]));
            }
        }

        {
            list[13].clear();
            list[13].setCommit(false);
            list[13].setFlag(false);
            list[13].setLength(2);
            list[13].addParameter(ui->buildComboBox->currentText());
            list[13].addParameter(ui->roomComboBox->currentText());
            list[13].postRequest("select id,name from proprietor where building_id=? and room_id = ?");

            QObject::connect(list[13].getReply() , &QNetworkReply::finished , [&]()
            {
                QList<QByteArray> info = list[13].getInfo().split('\n');

                int size = info[0].toInt();
                int rows = info[1].toInt();

                int sequence;
                for(int i = 0 ; i < size ; i ++)
                {
                    for(int j = 0 ; j < rows ; j++)
                    {
                        sequence = i*rows + j + 2;
                        if(j == 0)
                        {
                            ui->proprietorIdLabel->setText(QString(info[sequence]));
                        }
                        else if(j == 1)
                        {
                            ui->proprietorLabel->setText(QString(info[sequence]));
                        }
                    }
                }
            });
        }
    });

    /*

    //proprietor
    query.prepare("select id,name,organization,building_id, room_id,own_date from proprietor where building_id=?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    ui->tableView->model()->deleteLater();
    QStandardItemModel* pmodel = new QStandardItemModel();
    pmodel->setColumnCount(6);
    pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
    pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
    pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
    pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
    pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
    pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
    ui->tableView->setModel(pmodel);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,150);
    int rowNum=0;
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    */

    list[12].clear();
    list[12].setCommit(false);
    list[12].setFlag(false);
    list[12].setLength(1);
    list[12].addParameter(ui->buildComboBox->currentText());
    list[12].postRequest("select id,name,organization,building_id, room_id,own_date from proprietor where building_id=?");

    QObject::connect(list[12].getReply() , &QNetworkReply::finished , [&]()
    {
        ui->tableView->model()->deleteLater();
        QStandardItemModel* pmodel = new QStandardItemModel();
        pmodel->setColumnCount(6);
        pmodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("身份证号"));
        pmodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("姓名"));
        pmodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("工作单位"));
        pmodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("楼栋"));
        pmodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("房屋"));
        pmodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("入住日期"));
        ui->tableView->setModel(pmodel);
        //表头信息显示居左
        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        ui->tableView->setColumnWidth(0,150);
        int rowNum = 0;

        QList<QByteArray> info = list[12].getInfo().split('\n');

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
    });

    /*

    //label
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }

    */

    /*

    list[13].clear();
    list[13].setCommit(false);
    list[13].setFlag(false);
    list[13].setLength(2);
    list[13].addParameter(ui->buildComboBox->currentText());
    list[13].addParameter(ui->roomComboBox->currentText());
    list[13].postRequest("select id,name from proprietor where building_id=? and room_id = ?");

    QObject::connect(list[13].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[13].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                if(j == 0)
                {
                    ui->proprietorIdLabel->setText(QString(info[sequence]));
                }
                else if(j == 1)
                {
                    ui->proprietorLabel->setText(QString(info[sequence]));
                }
            }
        }
    });

    */
}

/*

HTTP& DelProprietorWidget::getHTTP()
{
    return DelProprietorWidget::http;
}

*/
