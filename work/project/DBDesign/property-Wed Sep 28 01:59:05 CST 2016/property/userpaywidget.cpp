#include "userpaywidget.h"
#include "ui_userpaywidget.h"

#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QStandardPaths>

//HTTP UserPayWidget::http;

UserPayWidget::UserPayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPayWidget)
{
    ui->setupUi(this);
    ui->feeTypecomboBox->addItem("未交");
    ui->feeTypecomboBox->addItem("已交");
    ui->feeTypecomboBox->addItem("全部");
    QSqlQuery query;
    //building
    query.exec("select building_id from building");

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->buildingComboBox->addItem(id);
    }

    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed=true");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    query.prepare("select id,name from proprietor where building_id=? and room_id=?");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorLabel->setText(query.value(0).toString());
        ui->nameLabel->setText(query.value(1).toString());
    }
}

UserPayWidget::~UserPayWidget()
{
    delete ui;
}

void UserPayWidget::on_buildingComboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    ui->proprietorLabel->setText("          ");
    ui->nameLabel->setText("      ");
    QSqlQuery query;
    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    //label
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorLabel->setText(query.value(0).toString());
        ui->nameLabel->setText(query.value(1).toString());
    }
}

void UserPayWidget::on_roomComboBox_currentIndexChanged(int index)
{
    // qDebug() << index;
    ui->proprietorLabel->setText("          ");
    ui->nameLabel->setText("      ");
    QSqlQuery query;
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next())
    {
        ui->proprietorLabel->setText(query.value(0).toString());
        ui->nameLabel->setText(query.value(1).toString());
    }
}

//print table

void UserPayWidget::printTable()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("./out.pdf");
    QPainter painter;
    if (! painter.begin(&printer))
    {
        // failed to open file
         qWarning("failed to open file, is it writable?");
         return ;
    }

    painter.drawText(200, 10, "物业缴费通知");
    int cell_w = 100;
    int cell_h = 30;
    int table_x = 80;
    int width = cell_w*4;
    int table_y = 80;
    int height = cell_h*8;
    QRect rect(table_x,table_y,width,height);
    painter.drawRect(rect);
    //横线
    for(int i=0;i<8;i++)
    {
       painter.drawLine(table_x,table_y+cell_h*i,table_x+width,table_y+cell_h*i);
    }
    //纵线
    painter.drawLine(table_x+cell_w,table_y,table_x+cell_w,table_y+height);
    painter.drawLine(table_x+2*cell_w,table_y,table_x+2*cell_w,table_y+cell_h*6);
    painter.drawLine(table_x+3*cell_w,table_y,table_x+3*cell_w,table_y+cell_h*7);
    painter.drawLine(table_x+4*cell_w,table_y,table_x+4*cell_w,table_y+cell_h*7);
     //纵向
    painter.drawText(table_x+5,table_y+20,"收费项目");
    painter.drawText(table_x+5,table_y+20+cell_h,"水费");
    painter.drawText(table_x+5,table_y+20+2*cell_h,"电费");
    painter.drawText(table_x+5,table_y+20+3*cell_h,"天然气费");
    painter.drawText(table_x+5,table_y+20+4*cell_h,"电视费用");
    painter.drawText(table_x+5,table_y+20+5*cell_h,"物业管理费用");
    painter.drawText(table_x+5,table_y+20+6*cell_h,"每月房贷");
    painter.drawText(table_x+5,table_y+20+7*cell_h,"合计");
    //横向
    painter.drawText(table_x+5+1*cell_w,table_y+20,"本月用量");
    painter.drawText(table_x+5+2*cell_w,table_y+20,"单价");
    painter.drawText(table_x+5+3*cell_w,table_y+20,"金额");
    QString id = ui->proprietorLabel->text();
    QString name = ui->nameLabel->text();
    QString b_id = ui->buildingComboBox->currentText();
    QString r_id = ui->roomComboBox->currentText();
    QString area;
    QString water;
    QString watt;
    QString gas;
    QString water_fee;
    QString watt_fee;
    QString gas_fee;
    QString tv_fee;
    QString prop_fee;
    QString mortage;
    QSqlQuery query;
    query.exec(QString("select area from room where building_id='%1' and room_id='%2' ").arg(b_id).arg(r_id));
    query.exec();
    while(query.next())
    {
        area = query.value(0).toString();
    }
    query.exec(QString("select water,watt,gas from meter where building_id='%1' and room_id='%2' and date='%3'").arg(b_id).arg(r_id).arg(ui->billDatecomboBox->currentText()));
    while(query.next())
    {
            water = query.value(0).toString();
            watt = query.value(1).toString();
            gas = query.value(2).toString();
    }
    query.exec(QString("select water,watt,gas,tv,property,mortage from month_bill where ID='%1' and date='%2' ").arg(id).arg(ui->billDatecomboBox->currentText()));
    while(query.next())
    {
       water_fee = query.value(0).toString();
       watt_fee= query.value(1).toString();
       gas_fee= query.value(2).toString();
       tv_fee= query.value(3).toString();
       prop_fee= query.value(4).toString();
       mortage= query.value(5).toString();
    }
    //
    painter.drawText(table_x+5+1*cell_w,table_y+20+1*cell_h,water);
    painter.drawText(table_x+5+1*cell_w,table_y+20+2*cell_h,watt);
    painter.drawText(table_x+5+1*cell_w,table_y+20+3*cell_h,gas);
    //unit price
    painter.drawText(table_x+5+2*cell_w,table_y+20+1*cell_h,QString("%1").arg(water_fee.toDouble()/water.toDouble()));
    painter.drawText(table_x+5+2*cell_w,table_y+20+2*cell_h,QString("%1").arg(watt_fee.toDouble()/watt.toDouble()));
    painter.drawText(table_x+5+2*cell_w,table_y+20+3*cell_h,QString("%1").arg(gas_fee.toDouble()/gas.toDouble()));
    painter.drawText(table_x+5+2*cell_w,table_y+20+4*cell_h,QString("%1").arg(tv_fee.toDouble()));
    painter.drawText(table_x+5+2*cell_w,table_y+20+5*cell_h,QString("%1").arg(prop_fee.toDouble()));
    //price
    painter.drawText(table_x+5+3*cell_w,table_y+20+1*cell_h,QString("%1").arg(water_fee));
    painter.drawText(table_x+5+3*cell_w,table_y+20+2*cell_h,QString("%1").arg(watt_fee));
    painter.drawText(table_x+5+3*cell_w,table_y+20+3*cell_h,QString("%1").arg(gas_fee));
    painter.drawText(table_x+5+3*cell_w,table_y+20+4*cell_h,QString("%1").arg(tv_fee));
    painter.drawText(table_x+5+3*cell_w,table_y+20+5*cell_h,QString("%1").arg(prop_fee));
    painter.drawText(table_x+5+3*cell_w,table_y+20+6*cell_h,QString("%1").arg(mortage));
    //sum
    painter.drawText(table_x+5+1*cell_w,table_y+20+7*cell_h,QString("%1").arg(water_fee.toDouble()+watt_fee.toDouble()+gas_fee.toDouble()+tv_fee.toDouble()+prop_fee.toDouble()+mortage.toDouble()));

    //user info
    painter.drawText(table_x+5,table_y+20-2*cell_h,QString("ID:%1").arg(id));
    painter.drawText(table_x+5+2*cell_w,table_y+20-2*cell_h,QString("姓名:%1").arg(name));
    painter.drawText(table_x+5+0*cell_w,table_y+20-cell_h,QString("楼栋:%1").arg(b_id));
    painter.drawText(table_x+5+1*cell_w,table_y+20-cell_h,QString("房屋:%1").arg(r_id));
    painter.drawText(table_x+5+2*cell_w,table_y+20-cell_h,QString("面积:%1").arg(area));
    painter.drawText(table_x+5+3*cell_w,table_y+20-cell_h,QString("日期:%1").arg(ui->billDatecomboBox->currentText()));

//     if (!printer.newPage()) {
//         qWarning("failed in flushing page to disk, disk full?");
//         return ;
//     }
     painter.end();
     QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("打印完成"),QMessageBox::Yes);

}

void UserPayWidget::on_pushButton_2_clicked()
{

   // printTable();

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("update month_bill set payed = true where id=? and date=?");
    query.addBindValue(ui->proprietorLabel->text());
    query.addBindValue(ui->billDatecomboBox->currentText());
    if(!query.exec())
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

    if(ui->feeTypecomboBox->currentText().compare("未交") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where payed = false and id=?");
    }
    else if(ui->feeTypecomboBox->currentText().compare("已交") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where payed = true and id=?");
    }
    else if(ui->feeTypecomboBox->currentText().compare("全部") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where id=?");
    }

    query.addBindValue(ui->proprietorLabel->text());
    query.exec();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("账单日期"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("水费"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("电费"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("天然气费"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("电视费用"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("物业费用"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("月房贷款"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("交费情况"));
    ui->tableView->model()->deleteLater();
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    ui->billDatecomboBox->clear();
    while(query.next())
    {
        ui->billDatecomboBox->addItem(query.value(0).toString());
        int i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString()));
        //设置字符颜色
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
        model->setItem(i,3,new QStandardItem(query.value(3).toString() ));
        model->setItem(i,4,new QStandardItem(query.value(4).toString() ));
        model->setItem(i,5,new QStandardItem(query.value(5).toString()  ));
        model->setItem(i,6,new QStandardItem(query.value(6).toString()  ));
        if(query.value(7).toInt()==1)
        {
            model->setItem(i,7,new QStandardItem("已交"));
        }
        else
        {
            model->setItem(i,7,new QStandardItem("未交"));
        }
    }
}

void UserPayWidget::on_SelectPushButton_clicked()
{
    QSqlQuery query;
    if(ui->feeTypecomboBox->currentText().compare("未交") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where payed = false and id=?");
    }
    else if(ui->feeTypecomboBox->currentText().compare("已交") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where payed = true and id=?");
    }
    else if(ui->feeTypecomboBox->currentText().compare("全部") == 0)
    {
         query.prepare("select date,water,watt,gas,tv,property,mortage,payed from month_bill natural join proprietor  where id=?");
    }

    query.addBindValue(ui->proprietorLabel->text());
    query.exec();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(8);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("账单日期"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("水费"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("电费"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("天然气费"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("电视费用"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("物业费用"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("月房贷款"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("交费情况"));
    ui->tableView->model()->deleteLater();
    ui->tableView->setModel(model);

    //表头信息显示居左

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setColumnWidth(0,100);
    ui->billDatecomboBox->clear();
    while(query.next())
    {
        ui->billDatecomboBox->addItem(query.value(0).toString());
        int i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString()));
        //设置字符颜色
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
        model->setItem(i,3,new QStandardItem(query.value(3).toString() ));
        model->setItem(i,4,new QStandardItem(query.value(4).toString() ));
        model->setItem(i,5,new QStandardItem(query.value(5).toString()  ));
        model->setItem(i,6,new QStandardItem(query.value(6).toString()  ));
        if(query.value(7).toInt()==1)
        {
            model->setItem(i,7,new QStandardItem("已交"));
        }
        else
        {
            model->setItem(i,7,new QStandardItem("未交"));
        }
    }
}

void UserPayWidget::on_pushButton_clicked()
{
    printTable();
}

/*

HTTP& UserPayWidget::getHTTP()
{
    return UserPayWidget::http;
}

*/
