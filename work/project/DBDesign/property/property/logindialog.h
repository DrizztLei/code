#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "http.h"

#include <QDialog>
// #include <QSqlQuery>
#include <QNetworkReply>

#include <vector>

namespace Ui
{
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    static QString LOGIN_ID;
    // static HTTP& getHTTP();

signals:
    void checked();

private slots:
    void on_loginButton_clicked();
    void on_exitLoginButton_clicked();

private:
    Ui::LoginDialog *ui;
    std::vector<HTTP> list;
    const int size = 1;
    QString md5;

    // static HTTP http;
};

#endif // LOGINDIALOG_H
