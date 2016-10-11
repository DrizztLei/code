#include "recordmeterdialog.h"
#include "ui_recordmeterdialog.h"

#include <QDebug>
#include <QNetworkReply>

// HTTP RecordMeterDialog::http;

RecordMeterDialog::RecordMeterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordMeterDialog)
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

    list[0].clear();
    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setLength(0);
    list[0].postRequest("select building_id from building");

    QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
    {
        QList<QByteArray> info = list[0].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        int sequence;
        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
                ui->buildingomboBox->addItem(QString(info[sequence]));
            }
        }
    });

    /*

    ui->roomComboBox->clear();

    query.prepare("select room_id from room where building_id=?");
    query.addBindValue(ui->buildingomboBox->currentText());
    query.exec();

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    */

    list[1].clear();
    list[1].setFlag(false);
    list[1].setCommit(false);
    list[1].setLength(1);
    list[1].addParameter(ui->buildingomboBox->currentText());

    list[1].postRequest("select room_id from room where building_id=?");

    QObject::connect(list[1].getReply() , &QNetworkReply::finished , [&]()
    {
        ui->roomComboBox->clear();

        QList<QByteArray> info = list[1].getInfo().split('\n');

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

    // table

    model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("Building ID"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("Room ID"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("Date"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("Water(/m^3)"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("Watt(/d)"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("Gas(/m^3)"));
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->resizeColumnsToContents();

}

RecordMeterDialog::~RecordMeterDialog()
{
    delete ui;
}

void RecordMeterDialog::on_buildingomboBox_currentIndexChanged(int index)
{

    /*

    ui->roomComboBox->clear();
    QSqlQuery query;

    query.prepare("select room_id from room where building_id=?");
    query.addBindValue(ui->buildingomboBox->currentText());
    query.exec();

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    query.clear();

    */

    list[2].clear();
    list[2].setFlag(false);
    list[2].setCommit(false);
    list[2].setLength(1);
    list[2].addParameter(ui->buildingomboBox->currentText());

    list[2].postRequest("select room_id from room where building_id=?");

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
}

void RecordMeterDialog::on_insertRecordPushButton_clicked()
{
    int i = model->rowCount();

    model->setItem(i,0,new QStandardItem(ui->buildingomboBox->currentText()));
    //设置字符颜色
    model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
    //设置字符位置
    model->item(i,0)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,1,new QStandardItem(ui->roomComboBox->currentText()));
    model->setItem(i,2,new QStandardItem(ui->dateEdit->text()));
    model->setItem(i,3,new QStandardItem(ui->waterDoubleSpinBox->text()));
    model->setItem(i,4,new QStandardItem(ui->wattDoubleSpinBox->text()));
    model->setItem(i,5,new QStandardItem(ui->gasDoubleSpinBox->text()));
    ui->tableView->resizeColumnsToContents();

}



void RecordMeterDialog::on_confirmPushButton_clicked()
{

    int index = 3 , postSize = 0 , sequence = 0 , size = 0 , rows = 0;

    QList<QByteArray> info;

    QString postSQL = "";

    // QSqlQuery query;
    /*
     * get standard
    */
    //unit price variables

    /*

    double water_per_stere;
    double watt_per_degree;
    double gas_per_stere;
    double tv_per_month;
    double prop_per_sqare_month;
    double mortage;
    //get standard
    query.exec("select * from standard where start_date = (select max(start_date) from standard)");
    while(query.next())
    {
        water_per_stere         = query.value(1).toDouble();
        watt_per_degree         = query.value(2).toDouble();
        gas_per_stere           = query.value(3).toDouble();
        tv_per_month            = query.value(4).toDouble();
        prop_per_sqare_month    = query.value(5).toDouble();
        mortage                 = query.value(6).toDouble();
    }

    */

    double water_per_stere;
    double watt_per_degree;
    double gas_per_stere;
    double tv_per_month;
    double prop_per_sqare_month;
    double mortage;

    postSize = 0;
    postSQL = "select * from standard where start_date = (select max(start_date) from standard)";

    list[index].clear();
    list[index].setCommit(false);
    list[index].setFlag(false);
    list[index].setRollback(false);
    list[index].setTransaction(true);
    list[index].setSync(true);
    list[index].setLength(postSize);

    // list[index].addParameter();

    list[index].postRequest(postSQL);

    info = list[index].getInfo().split('\n');

    for(int i = 0 ; i < size ; i ++)
    {
        for(int j = 0 ; j < rows ; j++)
        {
            sequence = i*rows + j + 2;
            switch (j)
            {
                case 1:
                    water_per_stere = info[sequence].toDouble();
                    break;
                case 2:
                    watt_per_degree = info[sequence].toDouble();
                    break;
                case 3:
                    gas_per_stere = info[sequence].toDouble();
                    break;
                case 4:
                    tv_per_month = info[sequence].toDouble();
                    break;
                case 5:
                    prop_per_sqare_month = info[sequence].toDouble();
                    break;
                case 6:
                    mortage = info[sequence].toDouble();
                    break;
                default:
                    break;
            }
        }
    }

    index ++;

    /*
        transaction
        insert meters of room
        then genarate month_bill then
    */
    //start transaction

    /*

    QSqlDatabase::database().transaction();

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
        //get current meters
        building_id = model->item(i,0)->text();
        room_id     = model->item(i,1)->text();
        date        = model->item(i,2)->text();
        water       = model->item(i,3)->text().toDouble();
        watt        = model->item(i,4)->text().toDouble();
        gas         = model->item(i,5)->text().toDouble();
        //get last meters
        query.prepare("select water,watt,gas from meter where building_id=:b_id and room_id=:r_id and date="
                   "(select max(date) from meter where building_id=:b_id and room_id=:r_id)");
        query.bindValue(":building_id",building_id);
        query.bindValue(":room_id",room_id);
        query.exec();
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
       query.exec();
       //generating month bill
       query.prepare("select ID,area from proprietor natural join room"
                     "where building_id=? and room_id=?");
       query.addBindValue(building_id);
       query.addBindValue(room_id);
       query.exec();
       QString proprietorId;
       double area;
       while(query.next())
       {
           proprietorId = query.value(0).toString();
           area = query.value(1).toDouble();
       }
       water_fee = (water - last_water)*water_per_stere;
       watt_fee = (watt - last_watt)*watt_per_degree;
       gas_fee = (gas - last_gas)*gas_per_stere;
       tv_fee = tv_per_month;
       property_fee = prop_per_sqare_month*area;
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
       query.exec();
    }
    QSqlDatabase::database().commit();

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

    HTTP temp;
    for(int i=0; i< rowCount;i++)
    {
        //get current meters
        building_id = model->item(i,0)->text();
        room_id     = model->item(i,1)->text();
        date        = model->item(i,2)->text();
        water       = model->item(i,3)->text().toDouble();
        watt        = model->item(i,4)->text().toDouble();
        gas         = model->item(i,5)->text().toDouble();
        //get last meters

        /*

        query.prepare("select water,watt,gas from meter where building_id=:b_id and room_id=:r_id and date="
                   "(select max(date) from meter where building_id=:b_id and room_id=:r_id)");
        query.bindValue(":building_id",building_id);
        query.bindValue(":room_id",room_id);
        query.exec();
        while(query.next())
        {
            last_water = query.value(0).toDouble();
            last_watt = query.value(1).toDouble();
            last_gas = query.value(2).toDouble();
        }

        */

        postSize = 4;
        postSQL = "select water,watt,gas from meter where building_id=? and room_id=? and date=(select max(date) from meter where building_id=? and room_id=?)";

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(false);
        temp.setRollback(false);
        temp.setTransaction(false);
        temp.setSync(true);
        temp.setLength(postSize);

        temp.addParameter(building_id);
        temp.addParameter(room_id);
        temp.addParameter(building_id);
        temp.addParameter(room_id);


        temp.postRequest(postSQL);

        info = temp.getInfo().split('\n');

        size = info[0].toInt();
        rows = info[1].toInt();

        for(int i = 0 ; i < size ; i ++)
        {
            for(int j = 0 ; j < rows ; j++)
            {
                sequence = i*rows + j + 2;
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

        index ++;

        // insert a new record to table meter

        postSize = 6;
        postSQL = "insert into meter values(?, ?, ?, ?, ?, ?)";

        temp.clear();
        temp.setCommit(false);
        temp.setFlag(false);
        temp.setTransaction(false);
        temp.setRollback(false);
        temp.setFlag(false);
        temp.setSync(true);
        temp.setLength(postSize);

        temp.addParameter(building_id);
        temp.addParameter(room_id);
        temp.addParameter(date);
        temp.addParameter(QString::number(water));
        temp.addParameter(QString::number(watt));
        temp.addParameter(QString::number(gas));

        temp.postRequest(postSQL);


       //generating month bill

       postSize = 2;
       postSQL = "select ID,area from proprietor natural join room where building_id=? and room_id=?";

       temp.clear();
       temp.setCommit(false);
       temp.setFlag(false);
       temp.setTransaction(false);
       temp.setRollback(false);
       temp.setFlag(false);
       temp.setSync(true);
       temp.setLength(postSize);

       temp.addParameter(building_id);
       temp.addParameter(room_id);

       temp.postRequest(postSQL);

       QString proprietorId;
       double area;

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
                   proprietorId = QString(info[sequence]);
               }
               if(j == 1)
               {
                   area = info[sequence].toDouble();
               }
           }
       }

       water_fee = (water - last_water)*water_per_stere;
       watt_fee = (watt - last_watt)*watt_per_degree;
       gas_fee = (gas - last_gas)*gas_per_stere;
       tv_fee = tv_per_month;
       property_fee = prop_per_sqare_month*area;
       mortage_fee = mortage;

       //insert into month_bill

       postSize = 8;
       postSQL = "insert into month_bill values(?, ?, ?, ?, ?, ?, ?, ?, false";

       temp.clear();
       temp.setCommit(false);
       temp.setFlag(false);
       temp.setRollback(false);
       temp.setTransaction(false);
       temp.setRollback(false);
       temp.setSync(true);

       temp.addParameter(proprietorId);
       temp.addParameter(date);
       temp.addParameter(QString::number(water_fee));
       temp.addParameter(QString::number(watt_fee));
       temp.addParameter(QString::number(gas_fee));
       temp.addParameter(QString::number(tv_fee));
       temp.addParameter(QString::number(property_fee));
       temp.addParameter(QString::number(mortage_fee));

       temp.setLength(8);
       temp.postRequest(postSQL);

    }

    temp.clear();
    temp.setSync(true);
    temp.setCommit(true);
    temp.setLength(0);

    temp.postRequest("");

    // QSqlDatabase::database().commit();
}

/*

HTTP& RecordMeterDialog::getHTTP()
{
    return RecordMeterDialog::http;
}

*/
