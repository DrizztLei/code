#include "recordmeterwidget.h"
#include "ui_recordmeterwidget.h"

#include <QMessageBox>
#include <QDebug>

// HTTP RecordMeterWidget::http;

RecordMeterWidget::RecordMeterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordMeterWidget)
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

    HTTP temp;

    // QSqlQuery query;
    //building

    /*

    query.exec("select building_id from building");
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->buildingomboBox->addItem(id);
    }

    */

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(false);
    temp.setRollback(false);
    temp.setTransaction(false);
    temp.setSync(true);
    temp.setLength(0);

    temp.postRequest("select building_id from building");

    {
        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                QString id = info[sequence];
                if(j == 0)
                {
                    ui->buildingomboBox->addItem(id);
                }
            }
        }
    }

    /*

    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildingomboBox->currentText());
    query.exec();
    while(query.next()){
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }
    //table
    model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("抄表日期"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("水表读数"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("电表读数"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("天然气表读数"));
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);

    */

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(false);
    temp.setRollback(false);
    temp.setTransaction(false);
    temp.setSync(true);
    temp.setLength(1);
    temp.addParameter(ui->buildingomboBox->currentText());

    ui->roomComboBox->clear();

    temp.postRequest("select room_id from room where building_id=? and stayed = true");

    {
        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                QString id = info[sequence];
                if(j == 0)
                {
                    ui->roomComboBox->addItem(id);
                }
            }
        }
    }

    //table
    model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("楼栋"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("房屋"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("抄表日期"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("水表读数"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("电表读数"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("天然气表读数"));
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
}

RecordMeterWidget::~RecordMeterWidget()
{
    delete ui;
}

void RecordMeterWidget::on_buildingomboBox_currentIndexChanged(int index)
{

    // qDebug() << index ;

    /*

    ui->roomComboBox->clear();
    QSqlQuery query;
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildingomboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }
    query.clear();

    */

    HTTP temp;

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(false);
    temp.setRollback(false);
    temp.setTransaction(false);
    temp.setSync(true);
    temp.setLength(1);
    temp.addParameter(ui->buildingomboBox->currentText());

    temp.postRequest("select room_id from room where building_id=? and stayed = true");

    {

        ui->roomComboBox->clear();

        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                QString id = info[sequence];
                if(j == 0)
                {
                    ui->roomComboBox->addItem(id);
                }
            }
        }
    }
}

void RecordMeterWidget::on_insertRecordPushButton_clicked()
{
    int i = model->rowCount();

    model->setItem(i,0,new QStandardItem(ui->buildingomboBox->currentText()));
    //设置字符颜色
    model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
    //设置字符位置
    model->item(i,0)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,1,new QStandardItem(ui->roomComboBox->currentText() ));
    model->setItem(i,2,new QStandardItem(ui->dateEdit->text()  ));
    model->setItem(i,3,new QStandardItem(ui->waterDoubleSpinBox->text() ));
    model->setItem(i,4,new QStandardItem(ui->wattDoubleSpinBox->text() ));
    model->setItem(i,5,new QStandardItem(ui->gasDoubleSpinBox->text()  ));
    //ui->tableView->resizeColumnsToContents();
}

void RecordMeterWidget::on_confirmPushButton_clicked()
{
    // QSqlQuery query;

    HTTP temp;
    /*
     * get standard
    */

    // unit price variables

    /*

    double water_per_stere;
    double watt_per_degree;
    double gas_per_stere;
    double tv_per_month;
    double prop_per_sqare_month;
    double mortage;

    //get standard

    bool b = query.exec(QString("select * from standard where start_date = (select max(start_date) from standard where start_date<='%1')").arg(ui->dateEdit->text()));

    //query.addBindValue(ui->dateEdit->text());

    if(!b)
    {
         QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("出现错误"),QMessageBox::Yes);
         return;
    }

    // qDebug()<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";

    while(query.next())
    {
        water_per_stere         = query.value(1).toDouble();
        watt_per_degree         = query.value(2).toDouble();
        gas_per_stere           = query.value(3).toDouble();
        tv_per_month            = query.value(4).toDouble();
        prop_per_sqare_month    = query.value(5).toDouble();
        mortage                 = query.value(6).toDouble();

        qDebug()<<query.value(1).toString(); //<<"LLLLLLLLLLLLLL";
        qDebug()<<query.value(2).toString();
        qDebug()<<query.value(3).toString();
        qDebug()<<query.value(4).toString();
        qDebug()<<query.value(5).toString();
        qDebug()<<query.value(6).toString(); //<<"PPPPPPPPPPPPP";
    }

    */

    double water_per_stere;
    double watt_per_degree;
    double gas_per_stere;
    double tv_per_month;
    double prop_per_sqare_month;
    double mortage;

    //get standard

    temp.clear();
    temp.setCommit(false);
    temp.setFlag(true);
    temp.setRollback(false);
    temp.setTransaction(false);
    temp.setSync(true);
    temp.setLength(0);

    temp.postRequest(QString("select water_per_stere , watt_per_degree , gas_per_stere ,tv_per_month , prop_per_sqare_month , mortage from standard where start_date = (select max(start_date) from standard where start_date<='%1')").arg(ui->dateEdit->text()));

    {
        QList<QByteArray> info = temp.getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;

        if(temp.getFlag())
        {
            bool b = (QString(info[2]).compare("true") == 0);
            if(!b)
            {
                QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("出现错误"),QMessageBox::Yes);
                return;
            }
        }

        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows; j++)
            {
                sequence = i*rows + j + 3;
                switch (j)
                {
                    case 0:
                        water_per_stere = info[sequence].toDouble();
                        break;
                    case 1:
                        watt_per_degree = info[sequence].toDouble();
                        break;
                    case 2:
                        gas_per_stere = info[sequence].toDouble();
                        break;
                    case 3:
                        tv_per_month = info[sequence].toDouble();
                        break;
                    case 4:
                        prop_per_sqare_month = info[sequence].toDouble();
                        break;
                    case 5:
                        mortage = info[sequence].toDouble();
                        break;
                    default:
                        break;
                }
            }
        }
    }

    /*
        transaction
        insert meters of room
        then genarate month_bill then
    */

    /*

    //number of record to be inserted
    int rowCount = model->rowCount();
    //current record info
    QString building_id;
    QString room_id;
    QString date;
    double water;
    double watt;
    double gas;
    //meter of last month
    double last_water;
    double last_watt;
    double last_gas;
    //fee of this month
    double water_fee ;
    double watt_fee;
    double gas_fee;
    double tv_fee;
    double property_fee;
    double mortage_fee;
    //for every record in table view to be inserted
    for(int i=0; i< rowCount;i++)
    {
        //start transaction
        QSqlDatabase::database().transaction();
        //res of query.exec()
        bool res = true;
        //get current meters
        building_id = model->item(i,0)->text();
        room_id     = model->item(i,1)->text();
        date        = model->item(i,2)->text();
        water       = model->item(i,3)->text().toDouble();
        watt        = model->item(i,4)->text().toDouble();
        gas         = model->item(i,5)->text().toDouble();
        // qDebug()<<building_id<<"~~~~~~~~~~~~~~"<<room_id;
        //get last meters
        query.prepare("select water,watt,gas from meter where building_id=:b_id and room_id=:r_id and date= (select max(date) from meter where building_id=:b_id and room_id=:r_id)");
        query.bindValue(":building_id",building_id);
        query.bindValue(":room_id",room_id);
        res &= query.exec();
        while(query.next())
        {
            last_water = query.value(0).toDouble();
            last_watt = query.value(1).toDouble();
            last_gas = query.value(2).toDouble();
        }
       //insert a new record to table meter
       query.prepare("insert into meter values(:building_id, :room_id, :date, :water, :watt, :gas)");
       query.bindValue(":building_id",building_id);
       query.bindValue(":room_id",room_id);
       query.bindValue(":date",date);
       query.bindValue(":water",water);
       query.bindValue(":watt",watt);
       query.bindValue(":gas",gas);
       res &= query.exec();
       //generating month bill
       query.prepare("select id,area from proprietor natural join room where building_id=:b_id and room_id=:r_id");
       query.bindValue(":b_id",building_id);
       query.bindValue(":r_id",room_id);
       query.exec();
       QString proprietorId;
       double area;
       while(query.next())
       {
           proprietorId = query.value(0).toString();

           // qDebug()<<"!!!!!!!!!"<<proprietorId<<"!!!!!!!!!!!!!!!!!"<<area;

           area = query.value(1).toDouble();
       }

       water_fee = (water - last_water)*water_per_stere;
       watt_fee = (watt - last_watt)*watt_per_degree;
       gas_fee = (gas - last_gas)*gas_per_stere;
       tv_fee = tv_per_month;
       property_fee = prop_per_sqare_month*area;
       // qDebug()<<"property_fee============"<<property_fee;
       mortage_fee = mortage;

       //insert into month_bill

       query.prepare("insert into month_bill values(:id, :date, :water, :watt, :gas, :tv, :property, :mortage, false)");
       query.bindValue(":id",proprietorId);
       query.bindValue(":date",date);
       query.bindValue(":water",water_fee);
       query.bindValue(":watt",watt_fee);
       query.bindValue(":gas",gas_fee);
       query.bindValue(":tv",tv_fee);
       query.bindValue(":property",property_fee);
       query.bindValue(":mortage",mortage_fee);
       res &=query.exec();

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
       }
    }

    */

    //number of record to be inserted

    int rowCount = model->rowCount();

    //current record info

    QString building_id;
    QString room_id;
    QString date;
    double water;
    double watt;
    double gas;

    //meter of last month

    double last_water = 0;
    double last_watt = 0;
    double last_gas = 0;

    //fee of this month

    double water_fee ;
    double watt_fee;
    double gas_fee;
    double tv_fee;
    double property_fee;
    double mortage_fee;

    //for every record in table view to be inserted

    for(int i = 0; i < rowCount ; i++)
    {
        // res of query.exec()

        bool res = true;

        temp.clear();
        temp.setSync(true);
        temp.setTransaction(true);

        temp.setLength(0);

        temp.postRequest("");

        // get current meters

        building_id = model->item(i,0)->text();
        room_id     = model->item(i,1)->text();
        date        = model->item(i,2)->text();
        water       = model->item(i,3)->text().toDouble();
        watt        = model->item(i,4)->text().toDouble();
        gas         = model->item(i,5)->text().toDouble();

        //get last meters

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(true);
        temp.setRollback(false);
        temp.setTransaction(false);
        temp.setSync(true);
        temp.setLength(4);

        temp.addParameter(building_id);
        temp.addParameter(room_id);
        temp.addParameter(building_id);
        temp.addParameter(room_id);

        temp.postRequest("select water,watt,gas from meter where building_id=? and room_id=? and date = (select max(date) from meter where building_id=? and room_id=?)");
        {
            QList<QByteArray> info = temp.getInfo().split('\n');

            int size = info[0].toInt();
            int rows = info[1].toInt();

            int sequence;

            res &= (QString(info[2]).compare("true") == 0);
            if(!res)
            {
                QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("获取历史记录失败"),QMessageBox::Yes);
                continue;
            }

            for(int i = 0 ; i < size ; i ++)
            {
                for(int j = 0 ; j < rows ; j++)
                {
                    sequence = i*rows + j + 3;
                    switch (j)
                    {
                        case 0:
                            last_water = info[sequence].toDouble();
                            break;
                        case 1:
                            last_watt = info[sequence].toDouble();
                            break;
                        case 2:
                            last_gas = info[sequence].toDouble();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(true);
        temp.setRollback(false);
        temp.setTransaction(false);
        temp.setSync(true);
        temp.setLength(6);

        temp.addParameter(building_id);
        temp.addParameter(room_id);
        temp.addParameter(date);
        temp.addParameter(water);
        temp.addParameter(watt);
        temp.addParameter(gas);

        temp.postRequest("insert into meter values(? , ? , ? , ? , ? , ?)");
        {
            QList<QByteArray> info = temp.getInfo().split('\n');
            res &= (QString(info[2]).compare("true") == 0);

            if(!res)
            {
                QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("插入数据失败,键值重复"),QMessageBox::Yes);
                continue;
            }

        }

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(false);
        temp.setRollback(false);
        temp.setTransaction(false);
        temp.setSync(true);
        temp.setLength(2);

        temp.addParameter(building_id);
        temp.addParameter(room_id);

        temp.postRequest("select id , area from proprietor natural join room where building_id=? and room_id=?");

        QString proprietorId;
        double area;

        {
            QList<QByteArray> info = temp.getInfo().split('\n');

            int size = info[0].toInt();
            int rows = info[1].toInt();

            int sequence;
            for(int i = 0 ; i < size ; i ++)
            {
                for(int j = 0 ; j < rows ; j++)
                {
                    sequence = i*rows + j + 2;

                    switch (j)
                    {
                        case 0:
                            proprietorId = info[sequence];
                            break;
                        case 1:
                            area = info[sequence].toDouble();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        water_fee = (water - last_water)*water_per_stere;
        watt_fee = (watt - last_watt)*watt_per_degree;
        gas_fee = (gas - last_gas)*gas_per_stere;
        tv_fee = tv_per_month;
        property_fee = prop_per_sqare_month*area;
        mortage_fee = mortage;

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(true);
        temp.setRollback(false);
        temp.setTransaction(false);
        temp.setSync(true);
        temp.setLength(8);

        temp.addParameter(proprietorId);
        temp.addParameter(date);
        temp.addParameter(water_fee);
        temp.addParameter(watt_fee);
        temp.addParameter(gas_fee);
        temp.addParameter(tv_fee);
        temp.addParameter(property_fee);
        temp.addParameter(mortage_fee);

        temp.postRequest("insert into month_bill values(? , ? , ? , ? , ? , ? , ? , ? , false)");

        {
            QList<QByteArray> info = temp.getInfo().split('\n');
            res &= (QString(info[2]).compare("true") == 0);
        }

        if(!res)
        {
            temp.clear();
            temp.setLength(0);
            temp.setRollback(true);
            temp.setCommit(false);
            temp.setFlag(false);
            temp.setTransaction(false);
            temp.setSync(true);

            temp.postRequest("");

            // QSqlDatabase::database().rollback();
            QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作失败"),QMessageBox::Yes);
            return;
        }
        else
        {
            temp.clear();
            temp.setLength(0);
            temp.setRollback(false);
            temp.setCommit(true);
            temp.setFlag(false);
            temp.setTransaction(false);
            temp.setSync(true);

            temp.postRequest("");

            // QSqlDatabase::database().commit();
            QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作成功"),QMessageBox::Yes);
        }
    }
}

void RecordMeterWidget::on_pushButton_clicked()
{
    int i = ui->tableView->model()->rowCount();
    ui->tableView->model()->removeRow(i-1);
}

/*

HTTP& RecordMeterWidget::getHTTP()
{
    return RecordMeterWidget::http;
}

*/
