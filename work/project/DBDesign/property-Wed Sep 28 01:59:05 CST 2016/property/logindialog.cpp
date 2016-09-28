#include "logindialog.h"
#include "ui_logindialog.h"
#include "textformat.h"

#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>

//extern QSqlDatabase* db;

QString LOGIN_ID;
//HTTP LoginDialog::http;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{

    QString loginId = ui->loginNameLineEdit->text();
    QString pwd = ui->loginPasswdLineEdit->text();

    // calculate md5(pwd)

    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);

    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

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
