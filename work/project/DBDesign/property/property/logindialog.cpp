#include "logindialog.h"
#include "ui_logindialog.h"
#include "textformat.h"

#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkReply>

//extern QSqlDatabase* db;

QString LoginDialog::LOGIN_ID = "";

// HTTP LoginDialog::http;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    if(size != list.size())
    {
        list.clear();
        for(int i = 0 ; i < size ; i++)
        {
            list.push_back(HTTP());
        }
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{

    QString loginId = ui->loginNameLineEdit->text();
    QString pwd = ui->loginPasswdLineEdit->text();
    ui->loginNameLineEdit->clear();
    ui->loginPasswdLineEdit->clear();

    // calculate md5(pwd)

    md5.clear();
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);

    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

    LoginDialog::LOGIN_ID = QString(loginId);

    /*

    QSqlQuery query;

    // TextFormat::dealText(QString("a"), "select * from db " );
    // connect(&query , &QSqlQuery::bindValue , &TextFormat::dealText);
    // connect(&query,&QSqlQuery::addBindValue,&TextFormat::dealText);

    query.prepare("select password from user where login_id=?");
    query.addBindValue(loginId);
    query.exec();

    // accept();

    if(query.size()==1 && query.next())
    {
         QString value0 = query.value(0).toString();
         if(value0.compare(md5)==0)
         {
             LOGIN_ID=loginId;
             accept();
         }
         else
         {
             QMessageBox::warning(this, tr("Waring"),tr("password error!"),QMessageBox::Yes);
         }
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"), tr("user name error!"),QMessageBox::Yes);
    }
    query.clear();

    */

    list[0].clear();
    list[0].setFlag(false);
    list[0].setCommit(false);
    list[0].setSync(true);
    list[0].setLength(1);
    list[0].addParameter(loginId);
    list[0].postRequest("select password from user where login_id=?");

//    QObject::connect(list[0].getReply() , &QNetworkReply::finished , [&]()
//    {
        QList<QByteArray> info = list[0].getInfo().split('\n');

        int size = info[0].toInt();
        int rows = info[1].toInt();

        if(size == 1 && rows == 1)
        {
            QString value0 = info[2];

            if(value0.compare(md5) == 0)
            {
                accept();
            }
            else
            {
                QMessageBox::information(this, tr("Waring"), tr("核对失败"),QMessageBox::Yes);
            }
        }
        else
        {
            QMessageBox::information(this, tr("Waring"), tr("核对失败"),QMessageBox::Yes);
        }
//    });
}

void LoginDialog::on_exitLoginButton_clicked()
{
    close();
}

/*

HTTP& LoginDialog::getHTTP()
{
    return LoginDialog::http;
}

*/
