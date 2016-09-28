#include <QApplication>
#include <QTextCodec>

#include <stdlib.h>
#include <unistd.h>

#include "recordmeterwidget.h"
#include "mainwindow.h"
#include "connection.h"
#include "logindialog.h"
#include "http.h"

//enum USER_TYPE{CHARGER,MANAGER};
//USER_TYPE *type;

extern QString LOGIN_ID;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if(!createConnection())
    {
         return 1;
    }

    LoginDialog dlg;

    if(dlg.exec() == QDialog::Accepted)
    {
           MainWindow w(0,LOGIN_ID);
           w.show();
           return app.exec();
    }
    return 0;
}
