#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recordmeterdialog.h"
#include "recordmeterwidget.h"
#include "aboutdialog.h"
#include "contactdialog.h"
#include "addproprietorwidget.h"
#include "addchargerwidget.h"
#include "delproprietorwidget.h"
#include "delchargerwidget.h"
#include "setstandardwidget.h"
#include "userpaywidget.h"
#include "monthbillwidget.h"
#include "monthnotpayedwidget.h"
#include "monthbillreportwidget.h"
#include "seasonbillreportwidget.h"
#include "yearbillreportwidget.h"
#include "allproprietorwidget.h"
#include "allroomproprietor.h"
#include "logindialog.h"

#include <iostream>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDebug>
#include <QSqlQuery>
#include <QRect>
#include <QDesktopWidget>
#include <QNetworkReply>

// HTTP MainWindow::http;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent,QString id) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    loginId = id;

    if(list.size() != size)
    {
        list.clear();
        for(int i = 0 ; i < size ; i++)
        {
            list.push_back(HTTP());
        }
    }

    QList<QString> rights;

    QSqlQuery query;

    QString sql = "select function from user natural join role_func where login_id=?";

    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setSync(true);
    list[0].setLength(1);
    list[0].addParameter(LoginDialog::LOGIN_ID);
    list[0].postRequest(sql);

//    QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
//    {

        rights.clear();

        QList<QByteArray> info = list[0].getInfo().split('\n');

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
                    QString temp = info[sequence];
                    rights.append(temp);
                }
            }
        }

        QDesktopWidget * desktop = QApplication::desktop();
        QRect screen = desktop->screenGeometry();

        int width = screen.width();
        int height = screen.height();

        height = 0.730 * 0.5 * width ;
        move(width / 4 , height / 4); //height/2 - 0.618 * 0.5 * width * 0.5);
        resize(0.5 * width , height);

        setActions(rights);

//    });

    /*

    query.prepare(sql);
    query.addBindValue(loginId);
    query.exec();

    while(query.next())
    {
        QString temp = query.value(0).toString();
        rights.append(temp);
    }

    QDesktopWidget * desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();

    int width = screen.width();
    int height = screen.height();

    height = 0.730 * 0.5 * width ;

    move(width / 4 , height / 4); //height/2 - 0.618 * 0.5 * width * 0.5);

    resize(0.5 * width , height);
    setActions(rights);

    */

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setActions(QList<QString> list)
{
    if(list.contains("RECORD_METER"))
    {
        meterMenu = ui->menuBar->addMenu("抄表");

        inputMeterData = new QAction("输入",this);

        connect(inputMeterData , &QAction::triggered , this , &MainWindow::inputMeterDataSlot);

        meterMenu->addAction(inputMeterData);
    }
    if(list.contains("CHARGE_FEE"))
    {
        chargingMenu = ui->menuBar->addMenu("缴费");
        userPay = new QAction("用户缴费",this);
        allUserBill= new QAction("每月账单",this);

        connect(userPay , &QAction::triggered , this , &MainWindow::userPaySlot);
        connect(allUserBill , &QAction::triggered , this , &MainWindow::allUserBillSlot);

        chargingMenu->addAction(userPay);
        chargingMenu->addAction(allUserBill);

    }
    if(list.contains("REPORT_FORMS"))
    {
        reportMenu = ui->menuBar->addMenu("报表");
        monthBillAction = new QAction("月度报表",this);
        seasonBillAction =new QAction("季度报表",this);
        yearBillAction = new QAction("年度报表",this);

        connect(monthBillAction , &QAction::triggered , this , &MainWindow::monthBillSlot);
        connect(seasonBillAction, &QAction::triggered , this , &MainWindow::seasonBillSlot);
        connect(yearBillAction, &QAction::triggered , this , &MainWindow::yearBillSlot);

        reportMenu->addAction(monthBillAction);
        reportMenu->addAction(seasonBillAction);
        reportMenu->addAction(yearBillAction);

    }
    if(list.contains("ADD_DEL_PROPRIETOR"))
    {
        proprietorMenu  = ui->menuBar->addMenu("&基本信息");
        addProprietor   = new QAction("&添加业主",this);
        delProprietor   = new QAction("&删除业主",this);
        showAllProprietor = new QAction("显示业主信息",this);
        showAllRoom  =   new QAction("显示房屋信息",this);

        connect(addProprietor,&QAction::triggered ,this, &MainWindow::addProprietorSlot);
        connect(delProprietor,&QAction::triggered ,this, &MainWindow::delProprietorSlot);
        connect(showAllProprietor,&QAction::triggered,this,&MainWindow::showAllProprietorSlot);
        connect(showAllRoom,&QAction::triggered,this,&MainWindow::showAllRoomSlot);

        proprietorMenu->addAction(addProprietor);
        proprietorMenu->addAction(delProprietor);
        proprietorMenu->addAction(showAllProprietor);
        proprietorMenu->addAction(showAllRoom);
    }
    if(list.contains("ADD_DEL_CHARGER"))
    {
        chargerMenu  = ui->menuBar->addMenu("收费人员");
        addCharger   = new QAction("添加收费人员",this);
        delCharger   = new QAction("删除收费人员",this);

        connect(addCharger,&QAction::triggered,this,&MainWindow::addChargerSlot);
        connect(delCharger,&QAction::triggered,this,&MainWindow::delChargerSlot);

        chargerMenu->addAction(addCharger);
        chargerMenu->addAction(delCharger);
    }
    if(list.contains("SET_STANDARD"))
    {
        standardMenu = ui->menuBar->addMenu("收费标准");
        setStandard = new QAction("设置收费标准",this);
        connect(setStandard,&QAction::triggered,this,&MainWindow::setStandardSlot);

        standardMenu->addAction(setStandard);
    }
    //HELP
    help = ui->menuBar->addMenu("关于");
    about = new QAction("说明",this);
    contact = new QAction("联系",this);

    connect(about,&QAction::triggered,this,&MainWindow::aboutSlot);
    connect(contact,&QAction::triggered,this,&MainWindow::contactSlot);

    help->addAction(about);
    help->addAction(contact);
}

//RECORD_METER

void MainWindow::importMeterDataSlot()
{
    qDebug()<<"importMeterDataSlot";
}

void MainWindow::inputMeterDataSlot()
{
    qDebug()<<"inputMeterDataSlot";
    RecordMeterWidget* now=new RecordMeterWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();

}

//CHARGE_FEE

void  MainWindow::userPaySlot()
{
     qDebug()<<"userPaySlot";
     UserPayWidget* now=new UserPayWidget();
     int num = ui->centralWidget->layout()->count();
     if(num)
     {
         QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
         ui->centralWidget->layout()->removeWidget(p);
         p->deleteLater();
     }
     now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     ui->centralWidget->layout()->layout()->layout()->addWidget(now);
     ui->centralWidget->layout()->update();
}

void  MainWindow::allUserBillSlot()
{
    qDebug()<<"allUserBillSlot";
    MonthBillWidget* now = new MonthBillWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

void  MainWindow::monthShouldPayNotPaySlot()
{
    qDebug()<<"shouldPayNotPaySlot";
    MonthNotPayedWidget* now=new MonthNotPayedWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

//REPORT_FORMS

void  MainWindow::monthBillSlot()
{
    qDebug()<<"monthBillSlot";
    MonthBillReportWidget* now = new MonthBillReportWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

void  MainWindow::seasonBillSlot()
{
    qDebug()<<"seasonBillSlot";
    SeasonBillReportWidget* now = new SeasonBillReportWidget();
    int num = ui->centralWidget->layout()->count();
    if(num){
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();

}

void  MainWindow::yearBillSlot()
{
    qDebug()<<"yearBillSlot";
    YearBillReportWidget* now = new YearBillReportWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

//ADD_DEL_PROPRIETOR

void  MainWindow::addProprietorSlot()
{
    qDebug()<<"addProprietorSlot";
    AddProprietorWidget* now = new AddProprietorWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

void  MainWindow::delProprietorSlot()
{
     qDebug()<<"delProprietorSlot";
     DelProprietorWidget* now=new DelProprietorWidget();
     int num = ui->centralWidget->layout()->count();
     if(num)
     {
         QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
         ui->centralWidget->layout()->removeWidget(p);
         p->deleteLater();
     }
     now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     ui->centralWidget->layout()->layout()->layout()->addWidget(now);
     ui->centralWidget->layout()->update();
}

void MainWindow::showAllProprietorSlot()
{
    AllProprietorWidget* now = new AllProprietorWidget();
    int num = ui->centralWidget->layout()->count();
    if(num){
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

void MainWindow::showAllRoomSlot()
{
    AllRoomWidget* now = new AllRoomWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

//ADD_DEL_CHARGER

void  MainWindow::addChargerSlot()
{
    qDebug()<<"addChargerSlot";
    AddChargerWidget* now=new AddChargerWidget();
    int num = ui->centralWidget->layout()->count();
    if(num)
    {
        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
        ui->centralWidget->layout()->removeWidget(p);
        p->deleteLater();
    }
    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
    ui->centralWidget->layout()->update();
}

void  MainWindow::delChargerSlot()
{
     qDebug()<<"delChargerSlot";
     DelChargerWidget* now=new DelChargerWidget();
     int num = ui->centralWidget->layout()->count();
     if(num)
     {
         QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
         ui->centralWidget->layout()->removeWidget(p);
         p->deleteLater();
     }
     now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     ui->centralWidget->layout()->layout()->layout()->addWidget(now);
     ui->centralWidget->layout()->update();
}

//SET_STANDARD

void  MainWindow::setStandardSlot()
{
     qDebug()<<"setStandardSlot";
     setStandardWidget* now=new setStandardWidget();
     int num = ui->centralWidget->layout()->count();
     if(num)
     {
         QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
         ui->centralWidget->layout()->removeWidget(p);
         p->deleteLater();
     }
     now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     ui->centralWidget->layout()->layout()->layout()->addWidget(now);
     ui->centralWidget->layout()->update();

}

//help

void MainWindow::contactSlot()
{
    qDebug()<<"contactSlot";
    ContactDialog cdlg;
    cdlg.exec();
}

void MainWindow::aboutSlot()
{
    qDebug()<<"aboutSlot";
    AboutDialog adlg;
    adlg.exec();
}

void MainWindow::setCentralContent(QWidget* w)
{
    qDebug() << "setCentralContent";
    w->close();

//    int num = ui->centralWidget->layout()->count();
//    if(num){
//        QWidget * p = ui->centralWidget->layout()->itemAt(num-1)->widget();
//        ui->centralWidget->layout()->removeWidget(p);
//        p->deleteLater();
//    }
//    now->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    ui->centralWidget->layout()->layout()->layout()->addWidget(now);
//    ui->centralWidget->layout()->update();
}

/*

HTTP& MainWindow::getHTTP()
{
    return http;
}

*/
