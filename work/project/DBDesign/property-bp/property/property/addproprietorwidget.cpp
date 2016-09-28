#include "addproprietorwidget.h"
#include "ui_addproprietorwidget.h"

#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

HTTP AddProprietorWidget::http;

AddProprietorWidget::AddProprietorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProprietorWidget)
{
    ui->setupUi(this);

    QSqlQuery query;
    //building
    query.exec("select building_id from building");

    while(query.next())
    {
        QString id = query.value(0).toString();
        ui->buildingComboBox->addItem(id);
    }

    //proprietor
    query.exec("select id,name,building_id, room_id,own_date from proprietor");
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
    while(query.next())
    {
        rowNum = pmodel->rowCount();
        pmodel->setItem(rowNum,0,new QStandardItem(query.value(0).toString() ));
        pmodel->setItem(rowNum,1,new QStandardItem(query.value(1).toString() ));
        pmodel->setItem(rowNum,2,new QStandardItem(query.value(2).toString() ));
        pmodel->setItem(rowNum,3,new QStandardItem(query.value(3).toString() ));
        pmodel->setItem(rowNum,4,new QStandardItem(query.value(4).toString() ));
    }

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
        ui->roomComboBox->addItem(id);
    }

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
        model->setItem(i,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
    }
}

AddProprietorWidget::~AddProprietorWidget()
{
    delete ui;
}

void AddProprietorWidget::on_buildingComboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    ui->roomComboBox->clear();
    QSqlQuery query;
    query.prepare("select room_id from room where building_id=? and stayed = false");
    query.addBindValue(ui->buildingComboBox->currentText());
    qDebug() << "SELECT ROOM_ID FROM *? " << query.lastQuery() ;
    query.exec();
    while(query.next())
    {

        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

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
    while(query.next()){
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
    while(query.next()){
        i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
    }


}

void AddProprietorWidget::on_pushButton_clicked()
{

   if(ui->proprietorLineEdit->text().length()!=18 && ui->proprietorLineEdit->text().length()!=15){
       ui->proprietorLineEdit->clear();
       QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("身份证号错误"),QMessageBox::Yes);
       return;
   }
   if(ui->nameLineEdit->text().length()==0){
       QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("姓名不能为空"),QMessageBox::Yes);
       return;
   }
   if(ui->organizationLineEdit->text().length()==0){
       QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("工作单位不能为空"),QMessageBox::Yes);
       return;
   }
   if(ui->phone1LineEdit->text().length()==0){
       QMessageBox::warning(0,QMessageBox::trUtf8("提示"),QMessageBox::trUtf8("电话号码不能为空"),QMessageBox::Yes);
       return;
   }
   QString ID = ui->proprietorLineEdit->text();
   QString name = ui->nameLineEdit->text();
   QString organization = ui->organizationLineEdit->text();
   QString building_id = ui->buildingComboBox->currentText();
   QString room_id = ui->roomComboBox->currentText();
   QString own_date = ui->ownDateDateTimeEdit->text();


    QSqlDatabase::database().transaction();
    QSqlQuery query;
    bool res = false;
    query.prepare("insert into proprietor values(?,?,?,?,?,?)");
    query.addBindValue(ID);
    query.addBindValue(name);
    query.addBindValue(organization);
    query.addBindValue(building_id);
    query.addBindValue(room_id);
    query.addBindValue(own_date);
    res = query.exec();
    //phone_num
    query.prepare("insert into proprietor_phone_num values(?,?)");
    query.addBindValue(ui->phone1LineEdit->text());
    query.addBindValue(ui->proprietorLineEdit->text());
    res &= query.exec();
    if(ui->phone2Line->text().length()>1){
        query.prepare("insert into proprietor_phone_num values(?,?)");
        query.addBindValue(ui->phone2Line->text());
        query.addBindValue(ui->proprietorLineEdit->text());
        res &=  query.exec();
    }
    query.prepare("update room set stayed = true where building_id=? and room_id=?");
    query.addBindValue(building_id);
    query.addBindValue(room_id);
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


    ui->roomComboBox->clear();
    query.prepare("select room_id from room where building_id=? and stayed = false");
    query.addBindValue(ui->buildingComboBox->currentText());
    query.exec();
    while(query.next()){
        QString id = query.value(0).toString();
        ui->roomComboBox->addItem(id);
    }

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
    while(query.next()){
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
    while(query.next()){
        i = model->rowCount();
        model->setItem(i,0,new QStandardItem(query.value(0).toString() ));
        model->setItem(i,1,new QStandardItem(query.value(1).toString() ));
        model->setItem(i,2,new QStandardItem(query.value(2).toString() ));
    }

}

HTTP& AddProprietorWidget::getHTTP()
{
    return AddProprietorWidget::http;
}
