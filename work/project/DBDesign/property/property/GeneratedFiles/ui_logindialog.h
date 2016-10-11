/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *loginNamelabel;
    QLabel *loginPasswdLable;
    QLineEdit *loginNameLineEdit;
    QLineEdit *loginPasswdLineEdit;
    QPushButton *loginButton;
    QPushButton *exitLoginButton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(400, 300);
        loginNamelabel = new QLabel(LoginDialog);
        loginNamelabel->setObjectName(QStringLiteral("loginNamelabel"));
        loginNamelabel->setGeometry(QRect(70, 110, 54, 16));
        loginPasswdLable = new QLabel(LoginDialog);
        loginPasswdLable->setObjectName(QStringLiteral("loginPasswdLable"));
        loginPasswdLable->setGeometry(QRect(70, 180, 54, 12));
        loginNameLineEdit = new QLineEdit(LoginDialog);
        loginNameLineEdit->setObjectName(QStringLiteral("loginNameLineEdit"));
        loginNameLineEdit->setGeometry(QRect(182, 110, 131, 20));
        loginPasswdLineEdit = new QLineEdit(LoginDialog);
        loginPasswdLineEdit->setObjectName(QStringLiteral("loginPasswdLineEdit"));
        loginPasswdLineEdit->setGeometry(QRect(182, 170, 131, 20));
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(74, 232, 91, 31));
        exitLoginButton = new QPushButton(LoginDialog);
        exitLoginButton->setObjectName(QStringLiteral("exitLoginButton"));
        exitLoginButton->setGeometry(QRect(214, 232, 91, 31));

        retranslateUi(LoginDialog);
        QObject::connect(exitLoginButton, SIGNAL(clicked()), LoginDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login", 0));
        loginNamelabel->setText(QApplication::translate("LoginDialog", "\347\231\273\351\231\206ID\357\274\232", 0));
        loginPasswdLable->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", 0));
        loginButton->setText(QApplication::translate("LoginDialog", "\347\231\273\351\231\206", 0));
        exitLoginButton->setText(QApplication::translate("LoginDialog", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
