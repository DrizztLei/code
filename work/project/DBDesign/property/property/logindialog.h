#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "http.h"

#include <QDialog>
#include <QSqlQuery>

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
    static HTTP& getHTTP();
private slots:
    void on_loginButton_clicked();
    void on_exitLoginButton_clicked();

private:
    Ui::LoginDialog *ui;
    static HTTP http;
};

#endif // LOGINDIALOG_H
