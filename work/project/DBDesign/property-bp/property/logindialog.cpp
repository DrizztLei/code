#include "logindialog.h"
#include "ui_logindialog.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>

//extern QSqlDatabase* db;
QString LOGIN_ID;

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
    //calculate md5(pwd)
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

    QSqlQuery query;
    query.exec("select password from user where login_id='"+loginId+"'");

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
