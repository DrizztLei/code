#include "mainwindow.h"
#include "connection.h"
#include "logindialog.h"
#include <QApplication>
#include <QTextCodec>
#include "recordmeterwidget.h"

//enum USER_TYPE{CHARGER,MANAGER};
//USER_TYPE *type;

extern QString LOGIN_ID;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if(!createConnection())
    {
         return 1;
    }
    LoginDialog dlg; // 建立自己新建的类的对象dlg
    if(dlg.exec() == QDialog::Accepted) // 利用Accepted返回值判断按钮是否被按下
    {
           MainWindow w(0,LOGIN_ID);
           w.show();                   // 如果被按下，显示主窗口
           return a.exec();            // 程序一直执行，直到主窗口关闭
    }

    return 0;

}
