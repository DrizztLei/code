#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc , char ** argv){
    QApplication app(argc , argv);
    QLabel * label = new QLabel("HHHH");
    QPushButton * button = new QPushButton("TEST");
    QObject :: connect (button , SIGNAL(clicked()) , &app , SLOT(quit()));
    button -> show();
    label -> show();
    return app.exec();
}
