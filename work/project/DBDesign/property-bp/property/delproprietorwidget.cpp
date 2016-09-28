#include "delproprietorwidget.h"
#include "ui_delproprietorwidget.h"
#include <QMessageBox>
#include <QDebug>
DelProprietorWidget::DelProprietorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelProprietorWidget)
{
    ui->setupUi(this);
    QSqlQuery query;
    //building
    query.exec("select building_id from building");

    while(query.next()){
        QString id = query.value(0).toString();
        ui->buildComboBox->addItem(id);
    }
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
    while(query.next()){
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next()){
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next()){
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }

}

DelProprietorWidget::~DelProprietorWidget()
{
    delete ui;
}

void DelProprietorWidget::on_buildComboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    QSqlQuery query;
    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next()){
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

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
    while(query.next()){
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    //label
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next()){
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }
}

void DelProprietorWidget::on_roomComboBox_currentIndexChanged(int index)
{
    qDebug () << index;
    QSqlQuery query;

    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next()){
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }
}

void DelProprietorWidget::on_pushButton_clicked()
{
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
    if(!res){
         QSqlDatabase::database().rollback();
         QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作失败"),QMessageBox::Yes);
         return;
    }else{
         QSqlDatabase::database().commit();
         QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("操作成功"),QMessageBox::Yes);
         return;
    }

    //update table view
    //room
    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = true");
    query.addBindValue(ui->buildComboBox->currentText());
    query.exec();
    while(query.next()){
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

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
    while(query.next()){
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
        pmodel->setItem(rowNum,5,new QStandardItem(query.value(5).toString() ));
    }

    //label
    query.prepare("select id,name from proprietor where building_id=? and room_id = ?");
    query.addBindValue(ui->buildComboBox->currentText());
    query.addBindValue(ui->roomComboBox->currentText());
    query.exec();
    while(query.next()){
        ui->proprietorIdLabel->setText(query.value(0).toString());
        ui->proprietorLabel->setText(query.value(1).toString());
    }
}
